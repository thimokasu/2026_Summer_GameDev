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
	ColliderInfo info = {
		SHAPE::BOX,
		&trans_,
		TAG::STAGE,
		Layer::STAGE,
		ColliderBase::SetMask({Layer::ACTOR}),
		VGet(0.0f, 0.0f, 0.0f),
		VGet(0.0f, 0.0f, 0.0f),
		false,
		true,
	};

	std::shared_ptr<ColliderBox> collider =
		std::make_shared<ColliderBox>(info, halfSize_, this);
	ownColliders_.emplace(static_cast<int>(SHAPE::BOX), collider);
}
