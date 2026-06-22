#include "TestBox.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

TestBox::TestBox(void)
{
}

TestBox::TestBox(VECTOR pos)
{
	trans_.pos = pos;
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}

TestBox::~TestBox(void)
{
}

void TestBox::SubLoad(void)
{
}

void TestBox::SubInit(void)
{
	float angle = 45.0f * DX_PI_F / 180.0f;
	trans_.quaRot = Quaternion::Euler({ angle,angle,angle });
}

void TestBox::SubUpdate(void)
{
}

void TestBox::SubDraw(void)
{
}

void TestBox::SubRelease(void)
{
}

void TestBox::InitCollider(void)
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
