#include "SwordFightLoseCPU.h"
#include"SwordFIghtCPUHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"

void SwordFightLoseCPU::EnterT(SwordFIghtCPU* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFIghtCPU::animType_CPU::Lose_CPU, false);

}

void SwordFightLoseCPU::HandleInputT(SwordFIghtCPU* owner)
{
	if (owner->GetAnimController()->IsEnd())
	{
		owner->ChangeState<SwordFightIdleCPU>();
	}
}

void SwordFightLoseCPU::UpdateT(SwordFIghtCPU* owner)
{
}

void SwordFightLoseCPU::ExitT(SwordFIghtCPU* owner)
{
}
