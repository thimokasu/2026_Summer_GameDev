#include "AthleticMiniCloud.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"


void AthleticMiniCloud::SubLoad(void)
{
}

void AthleticMiniCloud::SubInit(void)
{
	entityKind_ = EntityKind::ATHLETIC_CLOUD;
}

void AthleticMiniCloud::SubUpdate(void)
{
}

void AthleticMiniCloud::SubDraw(void)
{
}

void AthleticMiniCloud::SubRelease(void)
{
}

void AthleticMiniCloud::InitCollider(void)
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

void AthleticMiniCloud::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);

}
