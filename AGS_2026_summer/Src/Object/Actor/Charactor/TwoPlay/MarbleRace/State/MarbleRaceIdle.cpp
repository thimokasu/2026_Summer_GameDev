#include "MarbleRaceIdle.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../../Camera/Camera.h"
#include"MarbleRaceMove.h"
#include"MarbleRaveAttack.h"
#include"../../../../../Common/AnimationController.h"

void MarbleRaceIdle::EnterT(MarbleRacePlayer* owner)
{
	isLoop_ = true;
	auto anim = owner->GetAnimController();
	anim->Play(1);
}

void MarbleRaceIdle::HandleInputT(MarbleRacePlayer* owner)
{
	int i = owner->GetUseController();
	if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FRONT,i).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT,i).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK,i).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT,i).now
		)
	{
		owner->ChangeState<MarbleRaceMove>();
	}if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION,i).down)
	{
		owner->ChangeState<MarbleRaceAttack>();
	}
}

void MarbleRaceIdle::UpdateT(MarbleRacePlayer* owner)
{
}

void MarbleRaceIdle::ExitT(MarbleRacePlayer* owner)
{
}
