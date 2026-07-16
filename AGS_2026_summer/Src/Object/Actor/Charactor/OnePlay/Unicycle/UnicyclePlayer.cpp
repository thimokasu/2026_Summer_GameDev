#include "UnicyclePlayer.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"

#include "../../../../../Utility/AsoUtility.h"

#include "../../../../Common/AnimationController.h"

UnicyclePlayer::UnicyclePlayer(void)
{
}

UnicyclePlayer::~UnicyclePlayer(void)
{
}

void UnicyclePlayer::SubLoad(void)
{
	trans_.modelId = MV1LoadModel("Data/Unicycle/Player/RedcycleOnly.mv1");
	riderTrans_.modelId = MV1LoadModel("Data/Unicycle/Player/Redcycler.mv1");
}

void UnicyclePlayer::SubInit(void)
{
	//一輪車の初期化
	entityKind_ = EntityKind::PLAYER;
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(1000);
	rigidBody_.SetMoveSpeed(1.0f);
	trans_.pos = VGet(50.0f, 5.0f, 0.0f);
	float scale = 0.5f;
	trans_.scl = VGet(scale, scale, scale);
	trans_.quaRotLocal = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadD(180.0f), 0.0f));

	//搭乗者の初期化
	riderTrans_.scl = VGet(scale, scale, scale);
	riderTrans_.quaRotLocal = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadD(180.0f), 0.0f));

	//アニメーションの登録
	animationController_ = std::make_unique<AnimationController>(trans_.modelId);
	animationController_->AddInFbx(0, 60.0f, 0);

	riderAnimation_ = std::make_unique<AnimationController>(riderTrans_.modelId);
	riderAnimation_->AddInFbx(0, 60.0f, 0);

	//搭乗者の位置を一輪車に合わせる
	riderTrans_.pos = VAdd(trans_.pos, riderOffset_);
	riderTrans_.Update();
	trans_.Update();

}

void UnicyclePlayer::SubUpdate(void)
{
	MoveInput();

	//アニメーションの更新
	riderAnimation_->Play(0, true);
	animationController_->Play(0, true);
	animationController_->Update();
	riderAnimation_->Update();

	//搭乗者の位置を一輪車に合わせる
	riderTrans_.pos = VAdd(trans_.pos, riderOffset_);
	riderTrans_.quaRot = trans_.quaRot;
	riderTrans_.Update();

	//落下時
	if(trans_.pos.y < -1.0f)
	{
		if (fallCallBack_)fallCallBack_();
	}

}

void UnicyclePlayer::SubDraw(void)
{
	MV1DrawModel(trans_.modelId);
	MV1DrawModel(riderTrans_.modelId);
}

void UnicyclePlayer::SubRelease(void)
{
}

void UnicyclePlayer::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	info.entityKind_ = EntityKind::PLAYER;
	float radius = 8.0f;
	VECTOR localPosTop = VGet(0.0f, 10.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, 5.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void UnicyclePlayer::MoveInput(void)
{
	VECTOR moveVec = { 0.0f, 0.0f, 0.0f };
	//if (!KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now)return;
	moveVec.z += 1.0f;
	//if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now) moveVec.z -= 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now) moveVec.x += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now) moveVec.x -= 1.0f;

	const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera().GetAngles();
	MATRIX camYaw = MGetRotY(cameraAngle.y);
	moveVec = VTransform(moveVec, camYaw);

	if (VSize(moveVec) > 0.0f)
	{
		moveVec = VNorm(moveVec);

		// 移動方向を向く
		trans_.quaRot = Quaternion::Euler(VGet(0.0f, atan2f(moveVec.x, moveVec.z), 0.0f));
	}
	trans_.pos = VAdd(trans_.pos, VScale(moveVec, rigidBody_.GetMoveSpeed()));
}
