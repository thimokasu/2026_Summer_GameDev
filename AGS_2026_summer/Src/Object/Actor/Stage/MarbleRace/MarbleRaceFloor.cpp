#include "MarbleRaceFloor.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void MarbleRaceFloor::SubInit(void)
{
}

void MarbleRaceFloor::SubLoad(void)
{
}

void MarbleRaceFloor::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}

void MarbleRaceFloor::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::STAGE;
	info.localPos_ = VGet(0, 0, 80);
	VECTOR halfSize = VGet(100, 10, 400);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, halfSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}
