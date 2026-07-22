#include "SwordFightDamageCPU.h"
#include"SwordFIghtCPUHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"

void SwordFightDamageCPU::EnterT(SwordFIghtCPU* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFIghtCPU::animType_CPU::Damage_CPU, false);
}

void SwordFightDamageCPU::HandleInputT(SwordFIghtCPU* owner)
{
	if (owner->GetAnimController()->IsEnd())
	{
		owner->ChangeState<SwordFightIdleCPU>();
	}
}

void SwordFightDamageCPU::UpdateT(SwordFIghtCPU* owner)
{
}

void SwordFightDamageCPU::ExitT(SwordFIghtCPU* owner)
{
}
