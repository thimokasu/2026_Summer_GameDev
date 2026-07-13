#include "CollisionManager.h"
#include"../../../Object/Actor/Collider/ColliderBase.h"
#include"CollisionLogic.h"

CollisionManager::CollisionManager(void)
{
}

CollisionManager::~CollisionManager(void)
{
}

void CollisionManager::AddCollider(ColliderBase* collider, int entityID)
{
	if (!collider)return;
	CollisionObject colObj;
	colObj.collider_ = collider;
	colObj.entityID_ = entityID;
	colliders_.push_back(colObj);
}

void CollisionManager::RemoveCollider(ColliderBase* collider)
{
	if (!collider)return;
	std::erase_if(
		colliders_, [collider](const CollisionObject& colObj)
		{
			return colObj.collider_ == collider;
		}
	);
}

void CollisionManager::ClearColliders(void)
{
	colliders_.clear();
	prevPairs_.clear();
}

void CollisionManager::DebugDraw(void)
{
	for (auto& p : debugContactPoint_)
	{
		DrawSphere3D(p, 2, 16, 0xff0000, 0x0000ff, true);
	}
	debugContactPoint_.clear();
}


void CollisionManager::DiffPairs(CollisionPairs& currentPairs, CollisionPairs& prevPairs, CollisionPairs& beginPairs, CollisionPairs& endPairs)
{
	//ペアの配列をソート
	auto norm = [](auto& v)
		{
			std::sort(v.begin(), v.end());
			v.erase(std::unique(v.begin(), v.end()), v.end());
		};
	norm(currentPairs);
	norm(prevPairs);

	beginPairs.clear();
	endPairs.clear();
	//2つのソート済み配列をポインタの進歩比較で差分
	std::size_t a = 0, b = 0;
	while (a < currentPairs.size() && b < prevPairs.size())
	{
		//今あるが過去にない
		//衝突
		if (currentPairs[a] < prevPairs[b])
		{
			beginPairs.push_back(currentPairs[a]); ++a;
		}
		//過去にあるが今ない
		//消失
		else if (prevPairs[b] < currentPairs[a])
		{
			endPairs.push_back(prevPairs[b]); ++b;
		}
		//どっちにもある
		//継続衝突
		else
		{
			++a; ++b;
		}
	}
	while (a < currentPairs.size())beginPairs.push_back(currentPairs[a++]);
	while (b < prevPairs.size())endPairs.push_back(prevPairs[b++]);
}

void CollisionManager::Update(void)
{
	//今フレームで衝突したペアのリスト
	CollisionPairs currentPairs;
	//登録されているコライダー同士の総当たり
	for (int i = 0; i < colliders_.size(); i++)
	{
		//非アクティブならスキップ
		if (!colliders_[i].collider_->GetColliderInfo().isActive_) continue;

		for (int j = i + 1; j < colliders_.size(); j++)
		{
			//非アクティブならスキップ
			if (!colliders_[j].collider_->GetColliderInfo().isActive_)continue;

			auto* a = colliders_[i].collider_;
			auto* b = colliders_[j].collider_;

			//レイヤーマスク判定
			if (!ColliderBase::IsLayerMatch(
				b->GetColliderInfo().layer_,
				a->GetColliderInfo().mask_)
				&&
				!ColliderBase::IsLayerMatch(
					a->GetColliderInfo().layer_,
					b->GetColliderInfo().mask_
				))continue;

			//ペア判定
			CollisionPairType pairType =
				CollisionLogic::GetCollisionPairType(
					a->GetColliderInfo().shape_,
					b->GetColliderInfo().shape_);
			//衝突ロジック
			CollisionResult result = CollisionLogic::DispatchCollision(pairType, a, b);
			bool isTrigger = a->GetColliderInfo().isTrigger_ || b->GetColliderInfo().isTrigger_;
			if (isTrigger)
			{
				if (!result.isHit)continue;
			}
			else
			{
			//当たってない場合はスキップ
			if (!result.isHit || result.penetration < PENETRATION_ALLOWANCE)continue;
			}
			//当たっているペアを保存
			auto idA = colliders_[i].entityID_;
			auto idB = colliders_[j].entityID_;
			//小さいほうのIDをファーストにしてペアを正規化
			currentPairs.push_back({ (std::min)(idA, idB), (std::max)(idA, idB) });
			//押し戻しや衝突点を保存する
			if (!isTrigger)
			{
			resolve_.push_back(CollisionResolve{ &a->GetOwnerActor(),&b->GetOwnerActor(),result });
			}
		}
	}
	//新規衝突ペアと消失ペアを摘出
	CollisionPairs begins, ends;
	DiffPairs(currentPairs, prevPairs_, begins, ends);

	//コールバック処理
	if (onBegin_)
	{
		for (auto [idA, idB] : begins)
		{
			if (idA == 0&&idB==1)
			{
				int a = 0;
			}
			onBegin_(idA, idB);
		}
	}
	if (onEnd_)
	{
		for (auto [idA, idB] : ends)
		{
			onEnd_(idA, idB);
		}
	}
	//次のフレームのために保持
	prevPairs_ = std::move(currentPairs);
}

void CollisionManager::Resolve(void)
{
	for (auto& resolve : resolve_)
	{
		float invMassA = resolve.actorA->GetRigidBody().GetInverseMass();
		float invMassB = resolve.actorB->GetRigidBody().GetInverseMass();
		float totalInvMass = invMassA + invMassB;

		if (totalInvMass == 0.0f) continue;

		ApplyCollisionForces(resolve, totalInvMass);
		PositionIntegration(resolve, totalInvMass);
	}
	resolve_.clear();
}

// =================================================================
// 適切なトルクの計算と適用
// =================================================================
void CollisionManager::ApplyBodyTorque(RigidBody& rb, Transform& trans, const VECTOR& r, const VECTOR& collisionForce, const VECTOR& normal, float sign)
{
	// DYNAMIC（物理演算対象）でなければ処理しない
	if (rb.GetBodyType() != RigidBody::BodyType::DYNAMIC) return;

	if (!rb.IsUsingGravity())return;

	// トルク計算：トルク = レバーアーム(r) × 力(force)
	// signはAかBかで向きを反転させるために使用
	VECTOR torque = VCross(r, VScale(collisionForce, sign));

	// 物理計算が暴走しないためのトルク上限設定（必要に応じて調整してください）
	float maxTorque = 0.01f;
	float torqueMag = sqrtf(VDot(torque, torque));

	if (torqueMag > maxTorque)
	{
		torque = VScale(torque, maxTorque / torqueMag);
	}

	// 剛体にトルクを適用
	rb.AddTorque(torque);
}

// =================================================================
// 直線速度の相殺（めり込み方向への移動を止める）
// =================================================================
void CollisionManager::CancelLinearVelocity(RigidBody& rb, const VECTOR& normal, float sign)
{
	if (rb.GetBodyType() != RigidBody::BodyType::DYNAMIC) return;

	float dotV = VDot(rb.GetVelocity(), normal);

	if ((sign > 0.0f && dotV > 0.0f) || (sign < 0.0f && dotV < 0.0f))
	{
		rb.SetVelocity(VSub(rb.GetVelocity(), VScale(normal, dotV)));
	}
}

// =================================================================
// 1. 回転・トルク・速度相殺のメイン処理
// =================================================================
void CollisionManager::ApplyCollisionForces(CollisionResolve resolve, float totalInvMass)
{
	auto& rbA = resolve.actorA->GetRigidBody();
	auto& rbB = resolve.actorB->GetRigidBody();
	auto& transA = resolve.actorA->GetTransform();
	auto& transB = resolve.actorB->GetTransform();

	float invMassA = rbA.GetInverseMass();
	float invMassB = rbB.GetInverseMass();

	debugContactPoint_.push_back(resolve.result.contactPoint);
	VECTOR rA = VSub(resolve.result.contactPoint, transA.pos);
	VECTOR rB = VSub(resolve.result.contactPoint, transB.pos);

	float inertiaScale = 4.0f;
	float invInertiaA = (rbA.GetBodyType() == RigidBody::BodyType::DYNAMIC) ? (invMassA * inertiaScale) : 0.0f;
	float invInertiaB = (rbB.GetBodyType() == RigidBody::BodyType::DYNAMIC) ? (invMassB * inertiaScale) : 0.0f;

	VECTOR rnA = VCross(rA, resolve.result.normal);
	VECTOR rnB = VCross(rB, resolve.result.normal);

	float angularComponentA = VDot(VCross(VScale(rnA, invInertiaA), rA), resolve.result.normal);
	float angularComponentB = VDot(VCross(VScale(rnB, invInertiaB), rB), resolve.result.normal);

	float totalEffectiveMass = totalInvMass + angularComponentA + angularComponentB;

	if (totalEffectiveMass > 0.0001f)
	{
		float pushForceMag = resolve.result.penetration / totalEffectiveMass;
		VECTOR collisionForce = VScale(resolve.result.normal, pushForceMag);

		ApplyBodyTorque(rbA, transA, rA, collisionForce, resolve.result.normal, 1.0f);
		ApplyBodyTorque(rbB, transB, rB, collisionForce, resolve.result.normal, -1.0f);
	}

	CancelLinearVelocity(rbA, resolve.result.normal, 1.0f);
	CancelLinearVelocity(rbB, resolve.result.normal, -1.0f);

	if (rbA.GetBodyType() == RigidBody::BodyType::DYNAMIC)
	{
		VECTOR angVel = rbA.GetAngularVelocity();
		rbA.SetAngularVelocity(VScale(angVel, 0.9f)); // 0.95は減衰係数（0.9?0.99で調整）
	}
	if (rbB.GetBodyType() == RigidBody::BodyType::DYNAMIC)
	{
		VECTOR angVel = rbB.GetAngularVelocity();
		rbB.SetAngularVelocity(VScale(angVel, 0.9f));
	}
}

// =================================================================
// 2. 位置の押し出し処理（めり込み解決）
// =================================================================
void CollisionManager::PositionIntegration(CollisionResolve resolve, float totalInvMass)
{
	auto& rbA = resolve.actorA->GetRigidBody();
	auto& rbB = resolve.actorB->GetRigidBody();
	auto& transA = resolve.actorA->GetTransform();
	auto& transB = resolve.actorB->GetTransform();

	float invMassA = rbA.GetInverseMass();
	float invMassB = rbB.GetInverseMass();

	float penetration = resolve.result.penetration;
	float slop = PENETRATION_ALLOWANCE; // ここにヘッダの値を活用
	float resolveAmount = (penetration > slop) ? (penetration - slop) : 0.0f;

	if (resolveAmount <= 0.0f) return; // 許容範囲内なら処理しない

	float ratioA = invMassA / totalInvMass;
	float ratioB = invMassB / totalInvMass;

	if (invMassA > 0.0f)
	{
		transA.pos = VAdd(transA.pos, VScale(resolve.result.normal, resolve.result.penetration * ratioA));
		if (resolve.result.normal.y > 0.5f)
		{
			rbA.ClearGravity();
			rbA.SetGrounded(true);
		}
	}

	if (invMassB > 0.0f)
	{
		transB.pos = VAdd(transB.pos, VScale(resolve.result.normal, -resolve.result.penetration * ratioB));
		if (resolve.result.normal.y < -0.5f)
		{
			rbB.ClearGravity();
			rbB.SetGrounded(true);
		}
	}
}