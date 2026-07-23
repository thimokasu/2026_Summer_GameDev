#include "MarbleRaceGoal.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void MarbleRaceGoal::SubInit(void)
{
trans_.pos = VGet(0, 20, 360);
}

void MarbleRaceGoal::SubLoad(void)
{
}

void MarbleRaceGoal::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}

void MarbleRaceGoal::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::MARBLE_GOAL;
	info.isTrigger_ = true;
	info.debugColor_ = GetColor(0, 255, 255);
	
	VECTOR halfSize = VGet(100, 10, 1);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, halfSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}
