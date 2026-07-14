#include "FeedJ_Cook.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"FeedJStateHeaders.h"

void FeedJ_Cook::EnterT(FeedJPlayer* owner)
{
}

void FeedJ_Cook::HandleInputT(FeedJPlayer* owner)
{
}

void FeedJ_Cook::UpdateT(FeedJPlayer* owner)
{
	if (!KEY::GetIns().GetInfo(KEY::KEY_TYPE::K_KEY_ACTION).now)
	{
		owner->ChangeState<FeedJ_IdleState>();
	}
}

void FeedJ_Cook::ExitT(FeedJPlayer* owner)
{
}
