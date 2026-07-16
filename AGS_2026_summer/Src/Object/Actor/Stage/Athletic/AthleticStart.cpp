#include "AthleticStart.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void AthleticStart::SubLoad(void)
{
}

void AthleticStart::SubInit(void)
{
	entityKind_ = EntityKind::STAGE;

}

void AthleticStart::SubUpdate(void)
{
}

void AthleticStart::SubDraw(void)
{
}

void AthleticStart::SubRelease(void)
{
}

void AthleticStart::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::STAGE;
	VECTOR fSize = VGet(20, 20, 20);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void AthleticStart::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}
