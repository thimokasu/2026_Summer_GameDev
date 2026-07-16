#include "SpikeDropStage.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void SpikeDropStage::SubLoad(void)
{
}

void SpikeDropStage::SubInit(void)
{
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
	VECTOR fSize = VGet(0, 0, 0);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}
