#include "FeedJ_Dash.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"FeedJStateHeaders.h"

void FeedJ_Dash::EnterT(FeedJPlayer* owner)
{
}

void FeedJ_Dash::HandleInputT(FeedJPlayer* owner)
{
}

void FeedJ_Dash::UpdateT(FeedJPlayer* owner)
{
	owner->ChangeState<FeedJ_IdleState>();
}

void FeedJ_Dash::ExitT(FeedJPlayer* owner)
{
}
