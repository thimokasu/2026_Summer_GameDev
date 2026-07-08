#include "FeedJ_IdleState.h"
#include<DxLib.h>
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"FeedJStateHeaders.h"
#include"../../../../Item/FeedJ/Food/FoodBase.h"
#include"../../../../Item/FeedJ/Container/ContainerBase.h"
void FeedJ_IdleState::EnterT(FeedJPlayer* owner)
{
	isLoop_ = true;
}

void FeedJ_IdleState::HandleInputT(FeedJPlayer* owner)
{
	if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FRONT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).now
		)
	{
		owner->ChangeState<FeedJ_Walk>();
	}
	else
	{
		owner->ChangeState<FeedJ_IdleState>();
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::L_KEY_ACTOIN).down)
	{
		auto* dashState = dynamic_cast<FeedJ_Dash*>(owner->GetState<FeedJ_Dash>());
		dashState->SetDashVec(owner->GetTransform().GetForward());
		owner->ChangeState<FeedJ_Dash>();
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION).down)
	{
		owner->OnContactTrigger();
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::K_KEY_ACTION).down)
	{
		auto item = owner->GetHoldItem();
		if (item != nullptr)
		{
			if (auto f = dynamic_cast<FoodBase*>(item))
			{
				
			}
			else if (auto c = dynamic_cast<ContainerBase*>(item))
			{

			}
		}
	}
}

void FeedJ_IdleState::UpdateT(FeedJPlayer* owner)
{
}

void FeedJ_IdleState::ExitT(FeedJPlayer* owner)
{
}
