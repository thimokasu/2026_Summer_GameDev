#include "SwordFightIdleCPU.h"
#include"SwordFIghtCPUHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"
#include"../../../../../Object/Actor/Manager/ActorManager.h"
void SwordFightIdleCPU::EnterT(SwordFIghtCPU* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFIghtCPU::animType_CPU::Idle_CPU, false);
}

void SwordFightIdleCPU::HandleInputT(SwordFIghtCPU* owner)
{
    auto players =
        owner->GetActorManager()->FindActorsByKind(EntityKind::PLAYER);

    if (!players.empty())
    {
        owner->ChangeState<SwordFightWalkCPU>();
    }
}

void SwordFightIdleCPU::UpdateT(SwordFIghtCPU* owner)
{
}

void SwordFightIdleCPU::ExitT(SwordFIghtCPU* owner)
{
}
