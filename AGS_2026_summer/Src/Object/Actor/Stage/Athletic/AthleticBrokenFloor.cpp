#include "AthleticBrokenFloor.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void AthleticBrokenFloor::SubLoad(void)
{
}

void AthleticBrokenFloor::SubInit(void)
{
	entityKind_ = EntityKind::STAGE;
}

void AthleticBrokenFloor::SubUpdate(void)
{
}

void AthleticBrokenFloor::SubDraw(void)
{
}

void AthleticBrokenFloor::SubRelease(void)
{
}

void AthleticBrokenFloor::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR});
	info.entityKind_ = EntityKind::STAGE;
	VECTOR fSize = VGet(20, 20, 20);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void AthleticBrokenFloor::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);

}
