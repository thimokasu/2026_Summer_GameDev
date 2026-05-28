#include "ReactionBlock.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"
#include <EffekseerForDXLib.h>

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

	trans_.modelId = MV1LoadModel("Data/Stage/ReactionBlock.mv1");
	const float scale = 0.113f;
	trans_.scl = VGet(scale, scale, scale);

}

void ReactionBlock::SubUpdate(void)
{    
	if (emitIntensity_ > 0.0f)
	{
		emitIntensity_ -= 0.01f;
		if (emitIntensity_ < 0.0f) emitIntensity_ = 0.0f;
	}
}

void ReactionBlock::SubDraw(void)
{
	//ƒ‚ƒfƒ‹‚ÌŽ©ŒÈ”­Œõ•Ï‰»
	int colorVal = static_cast<int>(emitIntensity_ * 255.0f);
	COLOR_F emitColor = { colorVal / 255.0f, colorVal / 255.0f, colorVal / 255.0f, 1.0f };
	MV1SetEmiColorScale(trans_.modelId, emitColor);
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

void ReactionBlock::StepOn()
{
	emitIntensity_ = 1.0f;
}


