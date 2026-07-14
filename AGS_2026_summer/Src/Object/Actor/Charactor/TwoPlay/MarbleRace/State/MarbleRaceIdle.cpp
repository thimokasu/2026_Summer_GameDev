#include "MarbleRaceIdle.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../../Camera/Camera.h"
#include"MarbleRaceMove.h"
#include"MarbleRaveAttack.h"
void MarbleRaceIdle::EnterT(MarbleRacePlayer* owner)
{
}

void MarbleRaceIdle::HandleInputT(MarbleRacePlayer* owner)
{
	if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FRONT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).now
		)
	{
		owner->ChangeState<MarbleRaceMove>();
	}if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION).down)
	{
		owner->ChangeState<MarbleRaveAttack>();
	}
}

void MarbleRaceIdle::UpdateT(MarbleRacePlayer* owner)
{
}

void MarbleRaceIdle::ExitT(MarbleRacePlayer* owner)
{
}
