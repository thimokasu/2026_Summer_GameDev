#include "Capsule.h"
#include<memory>
#include"../Collider/ColliderInfo.h"
#include"../Collider/ColliderBase.h"
#include"../Collider/ColliderCapsule.h"
Capsule::Capsule(void)
	: ShapeBase(), localPosTop_{ 0,50,0 }, localPosDown_{ 0,-50,0 }, radius_(20.0f)
{
}

Capsule::Capsule(float radius, VECTOR localPosTop, VECTOR localPosDown)
	:
	ShapeBase(),
	radius_(radius),
	localPosTop_(localPosTop),
	localPosDown_(localPosDown)
{
}

Capsule::~Capsule(void)
{
}

void Capsule::SubLoad(void)
{
}

void Capsule::SubInit(void)
{
}
void Capsule::SubUpdate(void)
{
}

void Capsule::SubDraw(void)
{
}

void Capsule::SubRelease(void)
{
}

void Capsule::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ ColliderLayer::ACTOR,ColliderLayer::STAGE });
	info.localPos_ = VECTOR{ 0,0,0 };
	info.localRot_ = VECTOR{ 0,0,0 };
	info.isTrigger_ = false;
	info.isActive_ = true;
	std::unique_ptr<ColliderCapsule> collider =
		std::make_unique<ColliderCapsule>(info, radius_, localPosTop_, localPosDown_, *this);
}