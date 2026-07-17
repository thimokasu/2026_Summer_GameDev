#include "FindingJPlayer.h"
#include"../../../../Manager/Generic/KeyManager.h"
#include"../../../../Manager/Game/SceneManager.h"
#include"../../Camera/Camera.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderCapsule.h"
#include "../../../../Manager/Resource/ResourceManager.h"
#include "../../../../Utility/AsoUtility.h"
#include "../../../Common/AnimationController.h"

FindingJPlayer::FindingJPlayer(void)
{
}



FindingJPlayer::~FindingJPlayer(void)
{
}

void FindingJPlayer::SubLoad(void)
{
	trans_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(SRC::FJ_PLAYER);
}

void FindingJPlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(1000);
	rigidBody_.SetMoveSpeed(1.8f);
	//モデルの初期設定
	trans_.pos = VGet(180.0f, 30.0f, 20.0f);
	float scale = 0.25f;
	trans_.scl = VGet(scale, scale, scale);
	trans_.quaRotLocal = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadD(180.0f), 0.0f));
	trans_.Update();
	//アニメーションの登録
	animationController_ = std::make_unique<AnimationController>(trans_.modelId);
	animationController_->AddInFbx(0, 30.0f, 0);
	animationController_->AddInFbx(1, 60.0f, 1);
	animationController_->Play(1);
}

void FindingJPlayer::SubUpdate(void)
{
	MoveInput();
	animationController_->Update();
}

void FindingJPlayer::SubDraw(void)
{
	//DrawFormatString(0.0f, 80.0f, 0xffffff, "%f,%f,%f", trans_.pos.x, trans_.pos.y, trans_.pos.z);
}

void FindingJPlayer::SubRelease(void)
{
}

void FindingJPlayer::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	float radius = 10.0f;
	VECTOR localPosTop = VGet(0.0f, 10.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, 5.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void FindingJPlayer::MoveInput(void)
{
	VECTOR moveVec = { 0.0f, 0.0f, 0.0f };

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now) moveVec.z += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now) moveVec.z -= 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now) moveVec.x += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now) moveVec.x -= 1.0f;
	
	const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera().GetAngles();
	MATRIX camYaw = MGetRotY(cameraAngle.y);
	moveVec = VTransform(moveVec, camYaw);

	if(VSize(moveVec) > 0.0f)
	{
		moveVec = VNorm(moveVec);
		animationController_->Play(0);
		// 移動方向を向く
		trans_.quaRot = Quaternion::Euler(VGet(0.0f, atan2f(moveVec.x, moveVec.z), 0.0f));
	}
	else
	{
		animationController_->Play(1);
	}
	trans_.pos = VAdd(trans_.pos, VScale(moveVec, rigidBody_.GetMoveSpeed()));
}
