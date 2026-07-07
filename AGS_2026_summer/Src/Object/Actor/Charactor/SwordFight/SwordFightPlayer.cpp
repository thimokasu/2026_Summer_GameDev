#include "SwordFightPlayer.h"
#include"../../../../Manager/Generic/KeyManager.h"
#include"../../../../Manager/Game/SceneManager.h"
#include"../../Camera/Camera.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderCapsule.h"

#include"../../../../Manager/Resource/ResourceManager.h"

SwordFightPlayer::SwordFightPlayer(void)
{
}

SwordFightPlayer::~SwordFightPlayer(void)
{
}

void SwordFightPlayer::SubLoad(void)
{
	trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(SRC::P1));
}

void SwordFightPlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(1000);
	rigidBody_.SetMoveSpeed(1.25f);
	trans_.pos = VGet(0.0f, 40.0f, 0.0f);
}

void SwordFightPlayer::SubUpdate(void)
{
	MoveInput();
}

void SwordFightPlayer::SubDraw(void)
{
}

void SwordFightPlayer::SubRelease(void)
{
}

void SwordFightPlayer::InitCollider(void)
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

void SwordFightPlayer::MoveInput(void)
{
	VECTOR moveVec = { 0.0f, 0.0f, 0.0f };

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now) moveVec.z += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now) moveVec.z -= 1.0f;
}
