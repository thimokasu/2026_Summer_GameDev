#include "AthleticPlayer.h"
#include<DxLib.h>
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../../../Manager/Game/UIManager.h"
#include"../../../../../Manager/Resource/ResourceManager.h"
#include"../../../../../Manager/System/EventSystem/EventManager.h"
#include"../../../Camera/Camera.h"

#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"../../../Collider/ColliderSphere.h"

AthleticPlayer::AthleticPlayer(void)
{
}

AthleticPlayer::~AthleticPlayer(void)
{
}

void AthleticPlayer::SubLoad(void)
{
}

void AthleticPlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	trans_.pos.y = 100;
}

void AthleticPlayer::SubUpdate(void)
{
	if (canInput_)
	{
	MoveInput();
	JumpInput();
	}
}

void AthleticPlayer::SubDraw(void)
{
}

void AthleticPlayer::SubRelease(void)
{
}

void AthleticPlayer::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE,Layer::ACTOR_TRIGGER });
	float radius = 4.0f;
	VECTOR localPosTop = VGet(0.0f, 10.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, -10.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

	//他プレイヤーから踏まれるための頭用センサーコライダー
	info.shape_ = ColliderShape::SPHERE;
	info.layer_ = ColliderLayer::ACTOR_TRIGGER;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	radius = 4.0f;
	info.localPos_ = VGet(0, 20, 0);
	info.isTrigger_ = true;
	info.debugColor_=GetColor(0,255,0);
	std::unique_ptr<ColliderSphere> collider2 = std::make_unique<ColliderSphere>(info, radius, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider2));
}

void AthleticPlayer::InitRigidBody(void)
{
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetMoveSpeed(1);
	rigidBody_.SetJumpForce(25);
}

void AthleticPlayer::MoveInput(void)
{

	VECTOR moveVec = { 0.0f,0.0f,0.0f };

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now) {
		moveVec.z += 1.0f;
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now) moveVec.z -= 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now) moveVec.x += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now) moveVec.x -= 1.0f;

	const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera().GetAngles();
	MATRIX camYaw = MGetRotY(cameraAngle.y);
	moveVec = VTransform(moveVec, camYaw);

	if (VSize(moveVec) > 0.0f)
	{
		moveVec = VNorm(moveVec);
	}
	float yaw = atan2f(moveVec.x, moveVec.z);
	trans_.pos = VAdd(trans_.pos, VScale(moveVec, rigidBody_.GetMoveSpeed()));
}

void AthleticPlayer::JumpInput(void)
{
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
	{
		rigidBody_.AddForce({ 0,rigidBody_.GetJumpForce(),0 });
	}
}
