#include "MarbleRaceHit.h"
#include"MarbleRaceIdle.h"
void MarbleRaceHit::EnterT(MarbleRacePlayer* owner)
{
	isLoop_ = true;
	stateFrame_ = 0;
}

void MarbleRaceHit::HandleInputT(MarbleRacePlayer* owner)
{
}

void MarbleRaceHit::UpdateT(MarbleRacePlayer* owner)
{
	if (stateFrame_ > 24)
	{
		owner->ChangeState<MarbleRaceIdle>();
	}
	auto back = owner->GetTransform().GetBack();
	owner->GetTransform().pos = VAdd(owner->GetTransform().pos, VScale(back, 1));
}

void MarbleRaceHit::ExitT(MarbleRacePlayer* owner)
{
}
