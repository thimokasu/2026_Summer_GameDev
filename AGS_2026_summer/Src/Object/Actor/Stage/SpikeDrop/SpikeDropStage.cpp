#include "SpikeDropStage.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void SpikeDropStage::SubLoad(void)
{
}

void SpikeDropStage::SubInit(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}

void SpikeDropStage::SubUpdate(void)
{
}

void SpikeDropStage::SubDraw(void)
{
}

void SpikeDropStage::SubRelease(void)
{
}

void SpikeDropStage::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	info.entityKind_ = EntityKind::STAGE;
	VECTOR fSize = VGet(200, 0, 10);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	info.entityKind_ = EntityKind::STAGE;
	info.localPos_ = VGet(-200, 100,0);
	fSize = VGet(10, 100, 10);
	collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	info.entityKind_ = EntityKind::STAGE;
	info.localPos_ = VGet(200, 100, 0);
	fSize = VGet(10, 100, 10);
	collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}
