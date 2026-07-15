#include "AthleticNormalFloor.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void AthleticNormalFloor::SubLoad(void)
{
}

void AthleticNormalFloor::SubInit(void)
{
	entityKind_ = EntityKind::STAGE;

}

void AthleticNormalFloor::SubUpdate(void)
{
}

void AthleticNormalFloor::SubDraw(void)
{
}

void AthleticNormalFloor::SubRelease(void)
{
}

void AthleticNormalFloor::InitCollider(void)
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

void AthleticNormalFloor::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);

}
