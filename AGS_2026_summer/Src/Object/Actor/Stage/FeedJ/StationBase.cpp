#include "StationBase.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

StationBase::StationBase(void)
{
}

StationBase::~StationBase(void)
{
}

StationBase::StationBase(VECTOR pos)
{
	trans_.pos = pos;
}

void StationBase::SubLoad(void)
{
}

void StationBase::SubInit(void)
{
	entityKind_ = EntityKind::STATION;
}

void StationBase::SubUpdate(void)
{
}

void StationBase::SubDraw(void)
{
}

void StationBase::SubRelease(void)
{
}

void StationBase::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STATION;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE,Layer::FOOD,Layer::CONTAINER });
	info.entityKind_ = EntityKind::STATION;
	VECTOR fSize=VGet(10,10,10);
	std::unique_ptr<ColliderBox>collider=
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

}

void StationBase::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetMass(0);
	rigidBody_.SetUseGravity(true);
}
