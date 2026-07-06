#include "FeedJ_IdleState.h"
#include<DxLib.h>
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"FeedJStateHeaders.h"

void FeedJ_IdleState::EnterT(FeedJPlayer* owner)
{
	if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FRONT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).now
		)
	{
		owner->ChangeState<FeedJ_Walk>();
	}
}

void FeedJ_IdleState::HandleInputT(FeedJPlayer* owner)
{
}

void FeedJ_IdleState::UpdateT(FeedJPlayer* owner)
{
}

void FeedJ_IdleState::ExitT(FeedJPlayer* owner)
{
}
