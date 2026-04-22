#include "CharactorBase.h"
#include<memory>
#include"../../../Object/Actor/Collider/ColliderCapsule.h"

CharactorBase::CharactorBase(void)
{
}

CharactorBase::~CharactorBase(void)
{
}

void CharactorBase::SubLoad(void)
{
}

void CharactorBase::SubInit(void)
{
}

void CharactorBase::SubUpdate(void)
{
}

void CharactorBase::SubDraw(void)
{
}

void CharactorBase::SubRelease(void)
{
}

void CharactorBase::InitCollider(void)
{
	ColliderInfo info = {
		SHAPE::CAPSULE,
		&trans_,
		TAG::PLAYER,
		Layer::ACTOR,
		ColliderBase::SetMask({Layer::ACTOR,Layer::STAGE}),
		VGet(0.0f, 0.0f, 0.0f),
		VGet(0.0f, 0.0f, 0.0f),
		false,
		true,
	};
	float radius = 50.0f;
	VECTOR localPostop = VGet(0.0f, 50.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, -50.0f, 0.0f);
	std::shared_ptr<ColliderCapsule> collider =
		std::make_shared<ColliderCapsule>(info, radius, localPostop, localPosDown, this);
	ownColliders_.emplace(static_cast<int>(SHAPE::CAPSULE), collider);
}