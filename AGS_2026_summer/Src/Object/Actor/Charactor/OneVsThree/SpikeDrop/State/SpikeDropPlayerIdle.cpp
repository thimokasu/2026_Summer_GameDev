#include "SpikeDropPlayerIdle.h"
#include<DxLib.h>
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"SpikeDropPlayerMove.h"
#include"SpikeDropPlayerJump.h"
void SpikeDropPlayerIdle::EnterT(SpikeDropPlayer* owner)
{
	isLoop_ = true;

}

void SpikeDropPlayerIdle::HandleInputT(SpikeDropPlayer* owner)
{
	if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FRONT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).now
		)
	{
		owner->ChangeState<SpikeDropPlayerMove>();
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
	{
		owner->ChangeState<SpikeDropPlayerJump>();
	}
}

void SpikeDropPlayerIdle::UpdateT(SpikeDropPlayer* owner)
{
}

void SpikeDropPlayerIdle::ExitT(SpikeDropPlayer* owner)
{
}
