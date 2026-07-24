#include "Dropper.h"
#include<memory>
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderBox.h"
#include"State/DropperDrop.h"
#include"State/DropperIdle.h"
#include"State/DropperMove.h"

Dropper::Dropper(void)
{
}

Dropper::~Dropper(void)
{
}

void Dropper::SubLoad(void)
{
	CharactorBase::SubLoad();
}

void Dropper::SubInit(void)
{
	CharactorBase::SubInit();
	entityKind_ = EntityKind::DROPPER;
	ChangeState<DropperIdle>();
	trans_.pos.y = 200;
}

void Dropper::SubUpdate(void)
{
	CharactorBase::SubUpdate();
	trans_.pos.y = 200;

}

void Dropper::SubDraw(void)
{
}

void Dropper::SubRelease(void)
{
}

void Dropper::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::STAGE });
	VECTOR fSize = VGet(38, 10, 8);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, fSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void Dropper::InitRigidBody(void)
{
	rigidBody_.SetUseGravity(false);
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetMoveSpeed(1);
}

void Dropper::ReturnToIdle(void)
{
	ChangeState<DropperIdle>();
}

void Dropper::CreateState(void)
{
	AddState(std::make_unique<DropperIdle>());
	AddState(std::make_unique<DropperMove>());
	AddState(std::make_unique<DropperDrop>());
}
