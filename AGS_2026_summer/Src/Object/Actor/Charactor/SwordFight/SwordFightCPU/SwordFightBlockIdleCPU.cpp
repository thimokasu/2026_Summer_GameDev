#include "SwordFightBlockIdleCPU.h"
#include"SwordFIghtCPUHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"


void SwordFightBlockIdleCPU::EnterT(SwordFIghtCPU* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFIghtCPU::animType_CPU::BlockIdle_CPU, false);
}

void SwordFightBlockIdleCPU::HandleInputT(SwordFIghtCPU* owner)
{
	if (owner->GetAnimController()->IsEnd())
	{
		owner->ChangeState<SwordFightIdleCPU>();
	}
}

void SwordFightBlockIdleCPU::UpdateT(SwordFIghtCPU* owner)
{
}

void SwordFightBlockIdleCPU::ExitT(SwordFIghtCPU* owner)
{
}
