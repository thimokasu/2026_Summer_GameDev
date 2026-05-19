#include "CollisionManager.h"
#include"../../../Object/Actor/Collider/ColliderBase.h"
#include"CollisionLogic.h"

CollisionManager::CollisionManager(void)
{
}

CollisionManager::~CollisionManager(void)
{
}

void CollisionManager::AddCollider(ColliderBase* collider,int entityID)
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
	while (a<currentPairs.size()&&b<prevPairs.size())
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
	while (b < currentPairs.size())endPairs.push_back(prevPairs[b++]);
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
			//当たってない場合はスキップ
			if (!result.isHit || result.penetration < PENETRATION_ALLOWANCE)continue;
			//当たっているペアを保存
			auto idA = colliders_[i].entityID_;
			auto idB = colliders_[j].entityID_;
			//小さいほうのIDをファーストにしてペアを正規化
			currentPairs.push_back({ (std::min)(idA, idB), (std::max)(idA, idB) });
			//押し戻しや衝突点を保存する
			resolve_.push_back(CollisionResolve{ a->GetOwnerActor(),b->GetOwnerActor(),result });
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

}
