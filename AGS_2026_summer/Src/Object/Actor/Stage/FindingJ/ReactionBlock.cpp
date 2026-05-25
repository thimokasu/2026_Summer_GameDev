#include "ReactionBlock.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"
ReactionBlock::ReactionBlock(void)
{
}

ReactionBlock::~ReactionBlock(void)
{
}

ReactionBlock::ReactionBlock(VECTOR pos)
{
	trans_.pos = pos;
}

void ReactionBlock::SubLoad(void)
{
}

void ReactionBlock::SubInit(void)
{
}

void ReactionBlock::SubUpdate(void)
{
}

void ReactionBlock::SubDraw(void)
{
}

void ReactionBlock::SubRelease(void)
{
}

void ReactionBlock::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.localPos_ = { 0.0f,0.0f,0.0f };
	info.localRot_ = { 0.0f,0.0f,0.0f };
	info.isTrigger_ = false;
	info.isActive_ = true;
	info.debugColor_ = GetColor(255, 0, 0);
	std::unique_ptr<ColliderBase> collider =
		std::make_unique<ColliderBox>(info, halfSize_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::BOX), std::move(collider));
}
