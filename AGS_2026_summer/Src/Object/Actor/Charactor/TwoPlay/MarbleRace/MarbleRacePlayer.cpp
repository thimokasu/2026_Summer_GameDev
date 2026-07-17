#include "MarbleRacePlayer.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"../../../Collider/ColliderSphere.h"
#include"State/MarbleRaceIdle.h"
#include"State/MarbleRaceMove.h"
#include"State/MarbleRaveAttack.h"

MarbleRacePlayer::MarbleRacePlayer(void)
{
}

MarbleRacePlayer::~MarbleRacePlayer(void)
{
}

void MarbleRacePlayer::SubLoad(void)
{
	CharactorBase::SubLoad();
}

void MarbleRacePlayer::SubInit(void)
{
	CharactorBase::SubInit();
	trans_.pos.y = 100;
}

void MarbleRacePlayer::SubUpdate(void)
{
	CharactorBase::SubUpdate();
}

void MarbleRacePlayer::SubDraw(void)
{
	DrawFormatString(0, 10, 0xffffff, "State:%s", currentState_->GetName());
}

void MarbleRacePlayer::SubRelease(void)
{
}

void MarbleRacePlayer::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMoveSpeed(1);
	rigidBody_.SetMass(10);
}

void MarbleRacePlayer::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE,Layer::FOOD,Layer::STATION,Layer::CONTAINER });
	info.entityKind_ = EntityKind::PLAYER;
	float radius = 10.0f;
	VECTOR localPosTop = VGet(0.0f, 10.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, -10.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

	info.shape_ = ColliderShape::SPHERE;
	info.layer_ = ColliderLayer::ACTOR_TRIGGER;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::PLAYER_TRIGGER;
	info.isTrigger_ = true;
	info.debugColor_ = GetColor(0, 200, 200);
	radius = 10.0f;
	std::unique_ptr<ColliderSphere>collider2 =
		std::make_unique<ColliderSphere>(info, radius, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider2));
}

void MarbleRacePlayer::ReturnToIdle(void)
{
	ChangeState<MarbleRaceIdle>();
}

void MarbleRacePlayer::CreateState(void)
{
	AddState(std::make_unique<MarbleRaceIdle>());
	AddState(std::make_unique<MarbleRaceMove>());
	AddState(std::make_unique<MarbleRaveAttack>());
}

