#include "Box.h"
#include<memory>
#include"../Collider/ColliderInfo.h"
#include"../Collider/ColliderBase.h"
#include"../Collider/ColliderBox.h"

Box::Box(void)
	: ShapeBase(), halfSize_{ 50.0f,50.0f,50.0f }
{
}

Box::Box(const VECTOR& halfSize)
	: ShapeBase(), halfSize_(halfSize)
{
}

Box::~Box(void)
{
}

void Box::SubLoad(void)
{
}

void Box::SubInit(void)
{
}

void Box::SubUpdate(void)
{
}

void Box::SubDraw(void)
{
}

void Box::SubRelease(void)
{
}

void Box::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ ColliderLayer::ACTOR,ColliderLayer::STAGE });
	info.localPos_ = VECTOR{ 0,0,0 };
	info.localRot_ = VECTOR{ 0,0,0 };
	info.isTrigger_ = false;
	info.isActive_ = true;
	std::unique_ptr<ColliderBox> collider =
		std::make_unique<ColliderBox>(info, halfSize_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::BOX), std::move(collider));
}