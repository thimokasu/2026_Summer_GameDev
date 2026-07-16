#include "AthleticSpinBox.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void AthleticSpinBox::SubLoad(void)
{
}

void AthleticSpinBox::SubInit(void)
{
	entityKind_ = EntityKind::STAGE;

}

void AthleticSpinBox::SubUpdate(void)
{
	static float count = 0;
	count += 0.05f;
	float angle = count * DX_PI_F / 180.0f;
	trans_.quaRot = Quaternion::Euler({ 0,0,angle });
}

void AthleticSpinBox::SubDraw(void)
{
}

void AthleticSpinBox::SubRelease(void)
{
}

void AthleticSpinBox::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::STAGE;
	VECTOR fSize = VGet(40, 40,40);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void AthleticSpinBox::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);

}
