#include "SwordFight_BlockIdle.h"
#include"SwordFIghtStateHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"

void SwordFight_BlockIdle::EnterT(SwordFightPlayer* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFightPlayer::animType::BlockIdle, false);

}

void SwordFight_BlockIdle::HandleInputT(SwordFightPlayer* owner)
{

	if (owner->GetAnimController()->IsEnd())
	{
		owner->ChangeState<SwordFight_Idle>();
	}
}

void SwordFight_BlockIdle::UpdateT(SwordFightPlayer* owner)
{
}

void SwordFight_BlockIdle::ExitT(SwordFightPlayer* owner)
{
}
