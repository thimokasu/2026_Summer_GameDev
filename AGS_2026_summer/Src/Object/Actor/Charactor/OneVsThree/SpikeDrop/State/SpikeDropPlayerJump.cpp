#include "SpikeDropPlayerJump.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../../Camera/Camera.h"
#include"SpikeDropPlayerJump.h"
#include"SpikeDropPlayerIdle.h"
void SpikeDropPlayerJump::EnterT(SpikeDropPlayer* owner)
{
	isLoop_ = true;
	owner->GetRigidBody().AddForce(VGet(0, owner->GetRigidBody().GetJumpForce(),0));
}

void SpikeDropPlayerJump::HandleInputT(SpikeDropPlayer* owner)
{
}

void SpikeDropPlayerJump::UpdateT(SpikeDropPlayer* owner)
{
	owner->ChangeState<SpikeDropPlayerIdle>();
}

void SpikeDropPlayerJump::ExitT(SpikeDropPlayer* owner)
{
}
