#include "ActorBase.h"
#include"../Common/AnimationController.h"
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
	trans_.Update();
}

void ActorBase::Draw(void)
{
	SubDraw();
	MV1DrawModel(trans_.modelId);
}

void ActorBase::Release(void)
{
	SubRelease();
}

void ActorBase::SetOwnerActor2Colliders(void)
{
}
