#include "CharactorBase.h"

CharactorBase::CharactorBase(void)
{
}

CharactorBase::~CharactorBase(void)
{
}

void CharactorBase::SubLoad(void)
{
	CreateState();
}

void CharactorBase::SubInit(void)
{
	InitRigidBody();
	ReturnToIdle();
}

void CharactorBase::SubUpdate(void)
{
	MoveInput();
	if (canInput_)
	{
	currentState_->HandleInput(this);
	currentState_->Update(this);
	}
	currentState_->DecreaseIdleTime();
	if (currentState_->GetIdleTime() <= 0 && !currentState_->GetIsLoop())
	{
		ReturnToIdle();
	}
	if (currentState_->GetStateFrame() >= currentState_->GetNextInputStartTime())
	{
		currentState_->OnCanChange();
	}
	currentState_->InCreaseStateFrame();
}

void CharactorBase::SubDraw(void)
{
}

void CharactorBase::SubRelease(void)
{
}

void CharactorBase::InitCollider(void)
{
}

