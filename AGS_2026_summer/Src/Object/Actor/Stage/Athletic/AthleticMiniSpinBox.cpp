#include "AthleticMiniSpinBox.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"


void AthleticMiniSpinBox::SubLoad(void)
{
}

void AthleticMiniSpinBox::SubInit(void)
{
}

void AthleticMiniSpinBox::SubUpdate(void)
{
	static float count = 0;
	count += -0.05f;
	float angle = count * DX_PI_F / 180.0f;
	trans_.quaRot = Quaternion::Euler({ 0,0,angle });
}

void AthleticMiniSpinBox::SubDraw(void)
{
}

void AthleticMiniSpinBox::SubRelease(void)
{
}

void AthleticMiniSpinBox::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	VECTOR fSize = VGet(20, 20, 20);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void AthleticMiniSpinBox::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);

}
