#include "SmallMarble.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderSphere.h"

void SmallMarble::SubLoad(void)
{
}

void SmallMarble::SubInit(void)
{
	entityKind_ = EntityKind::MARBLE;
}

void SmallMarble::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::SPHERE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	info.entityKind_ = EntityKind::MARBLE;

	float radius = 8;
	std::unique_ptr<ColliderSphere>collider =
		std::make_unique<ColliderSphere>(info, radius, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void SmallMarble::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(5);
}
