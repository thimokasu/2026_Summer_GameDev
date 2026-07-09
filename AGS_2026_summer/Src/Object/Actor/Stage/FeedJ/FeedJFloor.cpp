#include "FeedJFloor.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

FeedJFloor::FeedJFloor(void)
{
}

FeedJFloor::FeedJFloor(VECTOR pos)
{
	trans_.pos = pos;

}

FeedJFloor::FeedJFloor(VECTOR pos, VECTOR size)
{
	trans_.pos = pos;
	halfSize_ = size;
}

FeedJFloor::FeedJFloor(VECTOR pos, VECTOR size, VECTOR deg)
{
	halfSize_ = size;
	trans_.pos = pos;
	trans_.quaRot = Quaternion::Euler(deg);
}

FeedJFloor::~FeedJFloor(void)
{
}

void FeedJFloor::SubLoad(void)
{
}

void FeedJFloor::SubInit(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);

}

void FeedJFloor::SubUpdate(void)
{
}

void FeedJFloor::SubDraw(void)
{
}

void FeedJFloor::SubRelease(void)
{
}

void FeedJFloor::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR ,Layer::FOOD,Layer::STATION,Layer::CONTAINER});
	info.localPos_ = { 0.0f,0.0f,0.0f };
	info.localRot_ = { 0.0f,0.0f,0.0f };
	info.isTrigger_ = false;
	info.isActive_ = true;
	info.debugColor_ = GetColor(0, 255, 0);
	std::unique_ptr<ColliderBase> collider =
		std::make_unique<ColliderBox>(info, halfSize_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::BOX), std::move(collider));
}

