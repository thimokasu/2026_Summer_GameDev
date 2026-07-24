#include "MarbleRaceWall.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void MarbleRaceWall::SubInit(void)
{
}

void MarbleRaceWall::SubLoad(void)
{
}

void MarbleRaceWall::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}

void MarbleRaceWall::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::STAGE;
	info.localPos_ = VGet(-100, 20, 20);
	info.debugColor_ = GetColor(150, 150, 150);
	VECTOR halfSize = VGet(2, 10, 350);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, halfSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.debugColor_ = GetColor(150, 150, 150);
	info.localPos_ = VGet(100, 20, 20);
	halfSize = VGet(2, 10, 350);
	collider =
		std::make_unique<ColliderBox>(info, halfSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}
