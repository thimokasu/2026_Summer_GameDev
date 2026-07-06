#include "CharactorBase.h"
#include"IdleState.h"

CharactorBase::CharactorBase(void)
{
}

CharactorBase::~CharactorBase(void)
{
}

void CharactorBase::SubLoad(void)
{
	CreateState();
	AddState(std::make_unique<IdleState>());
	ChangeState<IdleState>();
}

void CharactorBase::SubInit(void)
{
}

void CharactorBase::SubUpdate(void)
{
	MoveInput();
	currentState_->HandleInput(this);
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

void CharactorBase::ReturnToIdle()
{
	ChangeState<IdleState>();
}

