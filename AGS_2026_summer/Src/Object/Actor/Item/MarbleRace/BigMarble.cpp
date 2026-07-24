#include "BigMarble.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderSphere.h"
void BigMarble::SubLoad(void)
{
}

void BigMarble::SubInit(void)
{
	entityKind_ = EntityKind::MARBLE;
}

void BigMarble::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::SPHERE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	info.entityKind_ = EntityKind::MARBLE;
	info.debugColor_ = GetColor(GetRand(255), GetRand(255), GetRand(255));
	float radius = 12;
	std::unique_ptr<ColliderSphere>collider =
		std::make_unique<ColliderSphere>(info, radius, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void BigMarble::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(15);
}
