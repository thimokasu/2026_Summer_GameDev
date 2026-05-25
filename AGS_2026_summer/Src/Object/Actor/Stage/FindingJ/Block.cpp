#include "Block.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

Block::Block(void)
{
}

Block::~Block(void)
{
}

Block::Block(VECTOR pos)
{
	trans_.pos = pos;
}

void Block::SubLoad(void)
{
}

void Block::SubInit(void)
{
}

void Block::SubUpdate(void)
{
}

void Block::SubDraw(void)
{
}

void Block::SubRelease(void)
{
}

void Block::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.localPos_ = { 0.0f,0.0f,0.0f };
	info.localRot_ = { 0.0f,0.0f,0.0f };
	info.isTrigger_ = false;
	info.isActive_ = true;

	std::unique_ptr<ColliderBase> collider =
		std::make_unique<ColliderBox>(info, halfSize_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::BOX), std::move(collider));
}
