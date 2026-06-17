#include "FindingJPlayer.h"
#include"../../../../Manager/Generic/KeyManager.h"
#include"../../../../Manager/Game/SceneManager.h"
#include"../../Camera/Camera.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderCapsule.h"

FindingJPlayer::FindingJPlayer(void)
{
}



FindingJPlayer::~FindingJPlayer(void)
{
}

void FindingJPlayer::SubLoad(void)
{
}

void FindingJPlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(1000);
	rigidBody_.SetMoveSpeed(1.25f);
	trans_.pos = VGet(0.0f, 40.0f, 0.0f);
}

void FindingJPlayer::SubUpdate(void)
{
	MoveInput();
}

void FindingJPlayer::SubDraw(void)
{
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
	VECTOR localPosDown = VGet(0.0f, -10.0f, 0.0f);
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
	}
	trans_.pos = VAdd(trans_.pos, VScale(moveVec, rigidBody_.GetMoveSpeed()));
}
