#include "ReactionBlock.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"
#include <EffekseerForDXLib.h>

ReactionBlock::ReactionBlock()
{
	handle_ = -1;
}

ReactionBlock::ReactionBlock(VECTOR pos)
{
	trans_.pos = pos;
}

ReactionBlock::~ReactionBlock()
{
	if (handle_ != -1) {
		DeleteEffekseerEffect(handle_);
		handle_ = -1;
	}
}

void ReactionBlock::SubInit(void)
{

	trans_.modelId = MV1LoadModel("Data/Stage/ReactionBlock.mv1");
	const float scale = 0.113f;
	trans_.scl = VGet(scale, scale, scale);

	//‚±‚ê‚¦‚Ó‚¥‚­‚µ‚ 
	//handle_ = LoadEffekseerEffect("Data/Effect/Light/light.efkpkg");
}

void ReactionBlock::SubUpdate(void)
{    
	UpdateEffekseer3D();
}

void ReactionBlock::SubDraw(void)
{
	DrawEffekseer3D();
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
	GlowEffect();
}

void ReactionBlock::GlowEffect(void)
{
	auto upPos = VAdd(halfSize_, trans_.pos);
	
	SetPosPlayingEffekseer3DEffect(handle_, upPos.x, upPos.y, upPos.z);
}
