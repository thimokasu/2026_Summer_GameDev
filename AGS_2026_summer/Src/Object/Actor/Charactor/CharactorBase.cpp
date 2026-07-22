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

	// êÅÇ¡îÚÇ—íÜ
	if (isKnockBack_)
	{
		knockBackFrame_--;

		if (knockBackFrame_ <= 0)
		{
			isKnockBack_ = false;
		}

		return;
	}

	MoveInput();
	currentState_->HandleInput(this);
	currentState_->DecreaseIdleTime();
	currentState_->Update(this);
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

void CharactorBase::KnockBack(VECTOR dir, float power)
{
	dir.y = 0.0f;


	if (VSize(dir) > 0.0f)
	{
		dir = VNorm(dir);
	}


	// êÅÇ¡îÚÇ—ë¨ìx
	VECTOR velocity =
		VScale(dir, power);


	// è≠Çµè„ï˚å¸Ç…Ç‡îÚÇŒÇ∑
	velocity.y = power * 0.4f;


	rigidBody_.SetVelocity(velocity);


	isKnockBack_ = true;
	knockBackFrame_ = 30;

	DrawFormatString(
		0,
		100,
		0xffffff,
		"KnockBack");


}
