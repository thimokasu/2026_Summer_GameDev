#include "AthleticCloud.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"


void AthleticCloud::SubLoad(void)
{
}

void AthleticCloud::SubInit(void)
{
	entityKind_ = EntityKind::ATHLETIC_CLOUD;
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}

void AthleticCloud::SubUpdate(void)
{
}

void AthleticCloud::SubDraw(void)
{
}

void AthleticCloud::SubRelease(void)
{
}

void AthleticCloud::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::ATHLETIC_CLOUD;

	VECTOR fSize = VGet(40, 40, 40);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}
