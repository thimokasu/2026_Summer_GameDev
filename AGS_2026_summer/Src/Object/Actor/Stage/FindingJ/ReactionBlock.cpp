#include "ReactionBlock.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"
#include"../../../../Manager/Resource/ResourceManager.h"

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
	//trans_.modelId = MV1LoadModel("Data/Stage/ReactionBlock.mv1");
	trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(SRC::REACTION_BLOCK));
}

void ReactionBlock::SubInit(void)
{
	const float scale = 0.113f;
	trans_.scl = VGet(scale, scale, scale);
	entityKind_ = EntityKind::REACTION_BLOCK;
}

void ReactionBlock::SubUpdate(void)
{
	if (emitIntensity_ > 0.0f)
	{
		// 1•bŠÔ‚É–ñ 2.0 ‚¸‚ÂŒ¸‚ç‚·
		emitIntensity_ -= 0.01f;
		if (emitIntensity_ < 0.0f) emitIntensity_ = 0.0f;
	}
}

void ReactionBlock::SubDraw(void)
{
	int colorVal = static_cast<int>(emitIntensity_ * 255.0f);
	COLOR_F emitColor = { colorVal / 255.0f, colorVal / 255.0f, colorVal / 255.0f, 1.0f };
	MV1SetEmiColorScale(trans_.modelId, emitColor);
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

void ReactionBlock::StepOn()
{
	emitIntensity_ = 1.0f;

}
