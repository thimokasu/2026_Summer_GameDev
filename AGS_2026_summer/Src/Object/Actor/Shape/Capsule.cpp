#include "Capsule.h"
#include<memory>
#include"../Collider/ColliderInfo.h"
#include"../Collider/ColliderBase.h"
#include"../Collider/ColliderCapsule.h"
#include"../../../Manager/Generic/KeyManager.h"

Capsule::Capsule(void)
	: ShapeBase(), localPosTop_{ 0,50,0 }, localPosDown_{ 0,-50,0 }, radius_(20.0f)
{
}

Capsule::Capsule(float radius, VECTOR localPosTop, VECTOR localPosDown)
	:
	ShapeBase(),
	radius_(radius),
	localPosTop_(localPosTop),
	localPosDown_(localPosDown)
{
}

Capsule::~Capsule(void)
{
}

void Capsule::SubLoad(void)
{
}

void Capsule::SubInit(void)
{
	trans_.pos = VECTOR{ 0,200,0 };
}
void Capsule::SubUpdate(void)
{
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_UP).now)
	{
		trans_.pos.z += 10;
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_DOWN).now	)
	{
		trans_.pos.z -= 10;
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now)
	{
		trans_.pos.x += 10;
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now)
	{
		trans_.pos.x -= 10;
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
	{
		rigidBody_.SetVelocity({0.0f, rigidBody_.GetJumpForce(), 0.0f});
	}
}

void Capsule::SubDraw(void)
{
}

void Capsule::SubRelease(void)
{
}

void Capsule::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ ColliderLayer::ACTOR,ColliderLayer::STAGE });
	info.localPos_ = VECTOR{ 0,0,0 };
	info.localRot_ = VECTOR{ 0,0,0 };
	info.isTrigger_ = false;
	info.isActive_ = true;
	std::unique_ptr<ColliderCapsule> collider =
		std::make_unique<ColliderCapsule>(info, radius_, localPosTop_, localPosDown_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::CAPSULE), std::move(collider));
}