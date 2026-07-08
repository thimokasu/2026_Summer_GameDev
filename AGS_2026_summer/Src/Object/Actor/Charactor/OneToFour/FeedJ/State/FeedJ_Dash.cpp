#include "FeedJ_Dash.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"FeedJStateHeaders.h"

void FeedJ_Dash::EnterT(FeedJPlayer* owner)
{
	idleTime_ = 35;
	stateFrame_ = 0;

}

void FeedJ_Dash::HandleInputT(FeedJPlayer* owner)
{
}

void FeedJ_Dash::UpdateT(FeedJPlayer* owner)
{
	if (stateFrame_ > 30)
	{
		if (owner->GetHoldItem())
		{
			owner->ChangeState<FeedJ_HoldState>();
		}
		else
		{
			owner->ChangeState<FeedJ_IdleState>();
		}
	}
	auto forward = owner->GetTransform().GetForward();
	owner->GetTransform().pos = VAdd(owner->GetTransform().pos, VScale(forward, 2));
}

void FeedJ_Dash::ExitT(FeedJPlayer* owner)
{
}
