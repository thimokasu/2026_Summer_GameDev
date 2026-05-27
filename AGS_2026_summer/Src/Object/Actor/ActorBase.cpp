#include "ActorBase.h"
#include"../Common/AnimationController.h"
#include"Collider/ColliderBase.h"

ActorBase::ActorBase(void)
{
}

ActorBase::~ActorBase(void)
{
}

void ActorBase::Load(void)
{
	SubLoad();
}

void ActorBase::Init(void)
{
	SubInit();
	InitCollider();
}

void ActorBase::Update(void)
{
	SubUpdate();
	rigidBody_.Update();
	Move();
	trans_.Update();
}

void ActorBase::Draw(void)
{
	SubDraw();
	if (isDraw_)MV1DrawModel(trans_.modelId);
}

void ActorBase::Release(void)
{
	SubRelease();
}

void ActorBase::Move(void)
{
	trans_.pos = VAdd(trans_.pos, rigidBody_.GetVelocity());
}
