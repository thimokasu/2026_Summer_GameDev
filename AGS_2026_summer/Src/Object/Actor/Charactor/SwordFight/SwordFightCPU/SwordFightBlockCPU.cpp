#include "SwordFightBlockCPU.h"
#include"SwordFIghtCPUHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"


void SwordFightBlockCPU::EnterT(SwordFIghtCPU* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFIghtCPU::animType_CPU::Block_CPU, false);
}

void SwordFightBlockCPU::HandleInputT(SwordFIghtCPU* owner)
{
	if (owner->GetAnimController()->IsEnd())
	{
		owner->ChangeState<SwordFightIdleCPU>();
	}
}

void SwordFightBlockCPU::UpdateT(SwordFIghtCPU* owner)
{
}

void SwordFightBlockCPU::ExitT(SwordFIghtCPU* owner)
{
}
