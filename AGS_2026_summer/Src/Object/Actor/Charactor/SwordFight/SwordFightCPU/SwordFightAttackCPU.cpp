#include "SwordFightAttackCPU.h"
#include"SwordFIghtCPUHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"


void SwordFightAttackCPU::EnterT(SwordFIghtCPU* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFIghtCPU::animType_CPU::Attack_CPU, false);
}

void SwordFightAttackCPU::HandleInputT(SwordFIghtCPU* owner)
{
	if (owner->GetAnimController()->IsEnd())
	{
		owner->ChangeState<SwordFightIdleCPU>();
	}
}

void SwordFightAttackCPU::UpdateT(SwordFIghtCPU* owner)
{
}

void SwordFightAttackCPU::ExitT(SwordFIghtCPU* owner)
{
}
