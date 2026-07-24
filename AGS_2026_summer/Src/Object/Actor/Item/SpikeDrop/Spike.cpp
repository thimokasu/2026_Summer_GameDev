#include "Spike.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderCapsule.h"
#include"../../Collider/ColliderBox.h"

Spike::Spike(void)
{
}

Spike::~Spike(void)
{
}

void Spike::SubLoad(void)
{
}

void Spike::SubInit(void)
{
}

void Spike::SubUpdate(void)
{
}

void Spike::SubDraw(void)
{
}

void Spike::SubRelease(void)
{
}

void Spike::InitCollider(void)
{
		ColliderInfo info;
	int i = 0;
	i = GetRand(2);
	if (i == 0)
	{
		info.shape_ = ColliderShape::CAPSULE;
		info.layer_ = ColliderLayer::ROTAINGBODY;
		info.mask_ = ColliderBase::SetMask({ Layer::ROTAINGBODY,Layer::STAGE });
		info.entityKind_ = EntityKind::SPIKE;
		float radius = 10;
		VECTOR localPosTop = VGet(-10, 0, 0);
		VECTOR localPosDown = VGet(10, 0, 0);
		info.debugColor_ = GetColor(0, 255, 255);
		std::unique_ptr<ColliderCapsule>collider2 =
			std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
		ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider2));

		info.shape_ = ColliderShape::BOX;
		info.layer_ = ColliderLayer::SCAFFOLD;
		info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
		info.entityKind_ = EntityKind::SCAFFOLD;
		info.localPos_ = VGet(0, 5, 0);
		VECTOR fSize = VGet(18, 5, 8);
		info.debugColor_ = GetColor(0, 255, 0);
		std::unique_ptr<ColliderBox>collider =
			std::make_unique<ColliderBox>(info, fSize, *this);
		ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

		info.shape_ = ColliderShape::BOX;
		info.layer_ = ColliderLayer::SPIKE;
		info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
		info.entityKind_ = EntityKind::SPIKE;
		info.localPos_ = VGet(0, -10, 0);
		info.isTrigger_ = true;
		info.debugColor_ = GetColor(0, 0, 255);
		fSize = VGet(14, 1, 8);
		collider =
			std::make_unique<ColliderBox>(info, fSize, *this);
		ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
	}
	else if (i == 1)
	{
		info.shape_ = ColliderShape::CAPSULE;
		info.layer_ = ColliderLayer::ROTAINGBODY;
		info.mask_ = ColliderBase::SetMask({ Layer::ROTAINGBODY ,Layer::STAGE });
		info.entityKind_ = EntityKind::SPIKE;
		float radius = 10;
		VECTOR localPosTop = VGet(-20, 0, 0);
		VECTOR localPosDown = VGet(20, 0, 0);
		info.debugColor_ = GetColor(0, 255, 255);
		std::unique_ptr<ColliderCapsule>collider2 =
			std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
		ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider2));

		info.shape_ = ColliderShape::BOX;
		info.layer_ = ColliderLayer::SCAFFOLD;
		info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
		info.entityKind_ = EntityKind::SCAFFOLD;
		info.localPos_ = VGet(0, 5, 0);
		info.debugColor_ = GetColor(0, 255, 0);
		VECTOR fSize = VGet(28, 5,8);
		std::unique_ptr<ColliderBox>collider =
			std::make_unique<ColliderBox>(info, fSize, *this);
		ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

		info.shape_ = ColliderShape::BOX;
		info.layer_ = ColliderLayer::SPIKE;
		info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
		info.entityKind_ = EntityKind::SPIKE;
		info.localPos_ = VGet(0, -10, 0);
		info.isTrigger_ = true;
		info.debugColor_ = GetColor(0, 0, 255);
		fSize = VGet(24, 1, 8);
		collider =
			std::make_unique<ColliderBox>(info, fSize, *this);
		ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
	}
	else if (i == 2)
	{
		info.shape_ = ColliderShape::CAPSULE;
		info.layer_ = ColliderLayer::ROTAINGBODY;
		info.mask_ = ColliderBase::SetMask({ Layer::ROTAINGBODY ,Layer::STAGE });
		info.entityKind_ = EntityKind::SPIKE;
		float radius = 10;
		VECTOR localPosTop = VGet(-30, 0, 0);
		VECTOR localPosDown = VGet(30, 0, 0);
		info.debugColor_ = GetColor(0, 255, 255);
		std::unique_ptr<ColliderCapsule>collider2 =
			std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
		ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider2));

		info.shape_ = ColliderShape::BOX;
		info.layer_ = ColliderLayer::SCAFFOLD;
		info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
		info.entityKind_ = EntityKind::SCAFFOLD;
		info.debugColor_ = GetColor(0, 255, 0);
		info.localPos_ = VGet(0, 5, 0);
		VECTOR fSize = VGet(38, 5, 8);
		std::unique_ptr<ColliderBox>collider =
			std::make_unique<ColliderBox>(info, fSize, *this);
		ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

		info.shape_ = ColliderShape::BOX;
		info.layer_ = ColliderLayer::SPIKE;
		info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
		info.entityKind_ = EntityKind::SPIKE;
		info.debugColor_ = GetColor(0, 0, 255);
		info.localPos_ = VGet(0, -10, 0);
		fSize = VGet(34, 1, 8);
		collider =
			std::make_unique<ColliderBox>(info, fSize, *this);
		ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
	}
}

void Spike::InitRigidBody(void)
{
	rigidBody_.SetUseRotation(true);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetMass(50);
}
