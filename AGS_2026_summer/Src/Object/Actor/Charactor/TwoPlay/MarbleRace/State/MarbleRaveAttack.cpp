#include "MarbleRaveAttack.h"
#include"../../../../../Common/AnimationController.h"
#include"MarbleRaceIdle.h"
void MarbleRaceAttack::EnterT(MarbleRacePlayer* owner)
{
	stateFrame_ = 0;
	isLoop_ = true;
	auto anim = owner->GetAnimController();
	anim->Play(2);
}

void MarbleRaceAttack::HandleInputT(MarbleRacePlayer* owner)
{
}

void MarbleRaceAttack::UpdateT(MarbleRacePlayer* owner)
{
	if (stateFrame_ > 30)
	{
		owner->ChangeState<MarbleRaceIdle>();
	}
	auto forward = owner->GetTransform().GetForward();
	owner->GetTransform().pos = VAdd(owner->GetTransform().pos, VScale(forward, 1));
}

void MarbleRaceAttack::ExitT(MarbleRacePlayer* owner)
{
}
