#include "Floor.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"
#include"../../../../Manager/Resource/ResourceManager.h"

Floor::Floor(void)
{
}

Floor::~Floor(void)
{
}

Floor::Floor(VECTOR pos)
{
	trans_.pos = pos;
}

void Floor::SubLoad(void)
{
	trans_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(SRC::FLOOR);
}

void Floor::SubInit(void)
{
	entityKind_ = EntityKind::BLOCK;
	const float scale = 0.1f;
	trans_.scl = VGet(scale, scale, scale);
	trans_.pos = VAdd(trans_.pos,VGet(0.0f, -10.0f, 0.0f));
	trans_.Update();
}

void Floor::SubUpdate(void)
{
}

void Floor::SubDraw(void)
{
}

void Floor::SubRelease(void)
{
}

void Floor::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::BLOCK;
	info.localPos_ = { 0.0f,0.0f,0.0f };
	info.localRot_ = { 0.0f,0.0f,0.0f };
	info.isTrigger_ = false;
	info.isActive_ = true;
	info.debugColor_ = GetColor(128, 128, 128);
	std::unique_ptr<ColliderBase> collider =
		std::make_unique<ColliderBox>(info, halfSize_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::BOX), std::move(collider));
}
