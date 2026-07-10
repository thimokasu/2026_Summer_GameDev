#include "FeedJ_HoldState.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"FeedJStateHeaders.h"
#include"../../../../Item/FeedJ/Food/FoodBase.h"
#include"../../../../Item/FeedJ/Container/ContainerBase.h"
void FeedJ_HoldState::EnterT(FeedJPlayer* owner)
{
	isLoop_ = true;
}

void FeedJ_HoldState::HandleInputT(FeedJPlayer* owner)
{
	if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FRONT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).now
		)
	{
		owner->ChangeState<FeedJ_HoldWalk>();
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::L_KEY_ACTOIN).down)
	{
		auto* dashState = dynamic_cast<FeedJ_Dash*>(owner->GetState<FeedJ_Dash>());
		dashState->SetDashVec(owner->GetTransform().GetForward());
		owner->ChangeState<FeedJ_Dash>();
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION).down)
	{
		auto item = owner->GetHoldItem();
		if (auto food = dynamic_cast<FoodBase*>(item))
		{
			if (owner->GetIsContact())
			{
				owner->OnContactTrigger();
			}
			else
			{
				food->Detach();
				food->Drop(owner);
				owner->ReleaseHoldItem();
				owner->ChangeState<FeedJ_IdleState>();
			}
		}
		else if (auto continer = dynamic_cast<ContainerBase*>(item))
		{
			owner->OnContactTrigger();
		}
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::K_KEY_ACTION).down)
	{
		auto* item = owner->GetHoldItem();
		if (auto food = dynamic_cast<FoodBase*>(item))
		{
			food->Detach();
			food->Throw(owner);
		owner->ReleaseHoldItem();
		owner->ChangeState<FeedJ_IdleState>();
		}
	}
}

void FeedJ_HoldState::UpdateT(FeedJPlayer* owner)
{
}

void FeedJ_HoldState::ExitT(FeedJPlayer* owner)
{
}
