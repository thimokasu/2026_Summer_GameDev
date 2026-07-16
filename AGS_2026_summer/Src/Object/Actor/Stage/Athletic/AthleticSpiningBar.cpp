#include "AthleticSpiningBar.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"
#include"../../Collider/ColliderCapsule.h"

void AthleticSpiningBar::SubLoad(void)
{
}

void AthleticSpiningBar::SubInit(void)
{
	entityKind_ = EntityKind::STAGE;

}

void AthleticSpiningBar::SubUpdate(void)
{
	static float count = 0;
	count += 0.5f;
	float angle = count * DX_PI_F / 180.0f;
	trans_.quaRot = Quaternion::Euler({ 0,angle,0 });
}

void AthleticSpiningBar::SubDraw(void)
{
}

void AthleticSpiningBar::SubRelease(void)
{
}

void AthleticSpiningBar::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::STAGE;
	VECTOR fSize = VGet(40, 40, 40);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::STAGE;
	float radius= 5;
	VECTOR localPosTop = VGet(0, 60, 0);
	VECTOR localPosDown = VGet(0, 60, 40);
	info.debugColor_ = GetColor(0, 255, 255);
	std::unique_ptr<ColliderCapsule>collider2 =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider2));
}

void AthleticSpiningBar::InitRigidBody(void)
{
rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}
