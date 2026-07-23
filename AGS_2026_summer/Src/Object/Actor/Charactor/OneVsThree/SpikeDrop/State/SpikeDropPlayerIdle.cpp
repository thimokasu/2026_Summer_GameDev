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
	int i=owner->GetUseController();
	if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FRONT,i).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT,i).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK,i).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT,i).now
		)
	{
		owner->ChangeState<SpikeDropPlayerMove>();
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE,i).down)
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
