#include "Cliff.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"
#include"../../../../Manager/Resource/ResourceManager.h"

Cliff::Cliff(void)
{
}

Cliff::~Cliff(void)
{
}

Cliff::Cliff(VECTOR pos)
{
	trans_.pos = pos;
}

void Cliff::SubLoad(void)
{
	trans_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(SRC::CLIFF);
}

void Cliff::SubInit(void)
{
	entityKind_ = EntityKind::CLIFF;
	const float scale = 0.35f;
	trans_.scl = VGet(scale, scale, scale);
	trans_.pos = VAdd(trans_.pos, VGet(0.0f, -70.0f, 0.0f));
	trans_.Update();
}

void Cliff::SubUpdate(void)
{
}

void Cliff::SubDraw(void)
{
}

void Cliff::SubRelease(void)
{
}

void Cliff::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.localPos_ = { 0.0f,0.0f,0.0f };
	info.localRot_ = { 0.0f,0.0f,0.0f };
	info.isTrigger_ = false;
	info.isActive_ = true;
	info.debugColor_ = GetColor(128, 128, 128);
	std::unique_ptr<ColliderBase> collider =
		std::make_unique<ColliderBox>(info, halfSize_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::BOX), std::move(collider));
}
