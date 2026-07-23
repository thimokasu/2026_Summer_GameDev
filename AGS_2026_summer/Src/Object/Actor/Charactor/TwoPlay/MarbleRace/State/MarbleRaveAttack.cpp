#include "MarbleRaveAttack.h"
#include"MarbleRaceIdle.h"
void MarbleRaceAttack::EnterT(MarbleRacePlayer* owner)
{
	stateFrame_ = 0;
	isLoop_ = true;
}

void MarbleRaceAttack::HandleInputT(MarbleRacePlayer* owner)
{
}

void MarbleRaceAttack::UpdateT(MarbleRacePlayer* owner)
{
	if (stateFrame_ > 12)
	{
		owner->ChangeState<MarbleRaceIdle>();
	}
	auto forward = owner->GetTransform().GetForward();
	owner->GetTransform().pos = VAdd(owner->GetTransform().pos, VScale(forward, 2));
}

void MarbleRaceAttack::ExitT(MarbleRacePlayer* owner)
{
}
