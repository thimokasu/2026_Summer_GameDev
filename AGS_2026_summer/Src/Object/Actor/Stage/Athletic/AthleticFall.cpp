#include "AthleticFall.h"

#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void AthleticFall::SubLoad(void)
{
}

void AthleticFall::SubInit(void)
{
	entityKind_ = EntityKind::ATHLETIC_FALL;
}

void AthleticFall::SubUpdate(void)
{
}

void AthleticFall::SubDraw(void)
{
}

void AthleticFall::SubRelease(void)
{
}

void AthleticFall::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::ATHLETIC_FALL;
	VECTOR fSize = VGet(1000, 2, 300);
	info.localPos_ = VGet(700, -10, 0);
	info.debugColor_ = GetColor(0, 100, 200);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void AthleticFall::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}

