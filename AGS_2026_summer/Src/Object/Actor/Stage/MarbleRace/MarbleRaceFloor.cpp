#include "MarbleRaceFloor.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"
#include"../../../../Manager/Resource/ResourceManager.h"
void MarbleRaceFloor::SubInit(void)
{
}

void MarbleRaceFloor::SubLoad(void)
{
	trans_.modelId = 0;
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
	info.debugColor_ = GetColor(100, 100, 100);
	VECTOR halfSize = VGet(100, 10, 400);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, halfSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}
