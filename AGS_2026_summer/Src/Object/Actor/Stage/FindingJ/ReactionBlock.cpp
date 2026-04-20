#include "ReactionBlock.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

ReactionBlock::ReactionBlock()
{
}

ReactionBlock::ReactionBlock(VECTOR pos)
{
	trans_.pos = pos;
}

ReactionBlock::~ReactionBlock()
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
		std::make_shared<ColliderBox>(info, halfSize_, this,GetColor(255,0,0));
	ownColliders_.emplace(static_cast<int>(SHAPE::BOX), collider);
}
