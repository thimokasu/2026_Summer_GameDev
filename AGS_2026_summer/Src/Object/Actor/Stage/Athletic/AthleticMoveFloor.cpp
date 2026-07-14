#include "AthleticMoveFloor.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"


void AthleticMoveFloor::SubLoad(void)
{
}

void AthleticMoveFloor::SubInit(void)
{
	
}

void AthleticMoveFloor::SubUpdate(void)
{
	timer_ += 0.01f;
	float offset = sinf(timer_) * amplitude_;
	trans_.pos = VAdd(startPos_, VGet(offset, 0, 0));
}

void AthleticMoveFloor::SubDraw(void)
{
}

void AthleticMoveFloor::SubRelease(void)
{
}

void AthleticMoveFloor::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	VECTOR fSize = VGet(20, 20, 20);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void AthleticMoveFloor::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);

}
