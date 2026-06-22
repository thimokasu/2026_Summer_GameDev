#include "TestFloor.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"


TestFloor::TestFloor(void)
{
}

TestFloor::TestFloor(VECTOR pos)
{
}

TestFloor::~TestFloor(void)
{
}

void TestFloor::SubLoad(void)
{
}

void TestFloor::SubInit(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}

void TestFloor::SubUpdate(void)
{
}

void TestFloor::SubDraw(void)
{
}

void TestFloor::SubRelease(void)
{
}

void TestFloor::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.localPos_ = { 0.0f,0.0f,0.0f };
	info.localRot_ = { 0.0f,0.0f,0.0f };
	info.isTrigger_ = false;
	info.isActive_ = true;
	info.debugColor_ = GetColor(0, 255, 0);
	std::unique_ptr<ColliderBase> collider =
		std::make_unique<ColliderBox>(info, halfSize_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::BOX), std::move(collider));
}

