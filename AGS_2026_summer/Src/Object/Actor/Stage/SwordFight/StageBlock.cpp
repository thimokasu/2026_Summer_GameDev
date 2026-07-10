#include "StageBlock.h"
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"
#include"../../../../Manager/Resource/ResourceManager.h"
StageBlock::StageBlock(void)
{
}

StageBlock::~StageBlock(void)
{
}

StageBlock::StageBlock(VECTOR pos)
{
	trans_.pos = pos;
}

void StageBlock::SubLoad(void)
{
	//trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(SRC::STAGE));
}

void StageBlock::SubInit(void)
{
	/*trans_.scl.x = 10.0f;
	trans_.scl.z = 10.0f;
	trans_.scl.y = 10.0f;
	trans_.Update();*/
	//trans_.pos = pos;
}

void StageBlock::SubUpdate(void)
{
}

void StageBlock::SubDraw(void)
{
}

void StageBlock::SubRelease(void)
{
}

void StageBlock::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.localPos_ = { 0.0f,0.0f,0.0f };
	info.localRot_ = { 0.0f,0.0f,0.0f };
	info.isTrigger_ = false;
	info.isActive_ = true;
	info.debugColor_ = GetColor(0, 255, 0);
	std::unique_ptr<ColliderBase> collider =
		std::make_unique<ColliderBox>(info, halfSize_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::BOX), std::move(collider));
}
