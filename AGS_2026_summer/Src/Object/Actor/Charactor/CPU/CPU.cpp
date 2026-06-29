#include "CPU.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderCapsule.h"

CPU::CPU(void)
{
}

CPU::~CPU(void)
{
}

CPU::CPU(VECTOR pos)
{
}

void CPU::SubLoad(void)
{
}

void CPU::SubInit(void)
{
}

void CPU::SubUpdate(void)
{
}

void CPU::SubDraw(void)
{
}

void CPU::SubRelease(void)
{
}

void CPU::InitCollider(void)
{
	ColliderInfo info = {
	SHAPE::CAPSULE,
	&trans_,
	TAG::PLAYER,
	Layer::ACTOR,
	ColliderBase::SetMask({Layer::ACTOR}),
	VGet(0.0f, 0.0f, 0.0f),
	VGet(0.0f, 0.0f, 0.0f),
	false,
	true,
	};

	std::shared_ptr<ColliderCapsule> collider =
		std::make_shared<ColliderCapsule>(info, radius_, topPos, downPos, this);
	ownColliders_.emplace(static_cast<int>(SHAPE::CAPSULE), collider);
}
