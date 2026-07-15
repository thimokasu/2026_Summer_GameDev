#include "AthleticGoal.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"


void AthleticGoal::SubLoad(void)
{
}

void AthleticGoal::SubInit(void)
{
	entityKind_ = EntityKind::ATHLETIC_GOAL;
}

void AthleticGoal::SubUpdate(void)
{
}

void AthleticGoal::SubDraw(void)
{
}

void AthleticGoal::SubRelease(void)
{
}

void AthleticGoal::InitCollider(void)
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

void AthleticGoal::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);

}
