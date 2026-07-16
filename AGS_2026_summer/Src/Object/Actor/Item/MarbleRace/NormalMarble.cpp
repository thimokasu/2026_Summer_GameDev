#include "NormalMarble.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderSphere.h"
void NormalMarble::SubLoad(void)
{
}

void NormalMarble::SubInit(void)
{
	entityKind_ = EntityKind::MARBLE;

}

void NormalMarble::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::SPHERE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	info.entityKind_ = EntityKind::MARBLE;

	float radius = 10;
	std::unique_ptr<ColliderSphere>collider =
		std::make_unique<ColliderSphere>(info, radius, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void NormalMarble::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(10);
}
