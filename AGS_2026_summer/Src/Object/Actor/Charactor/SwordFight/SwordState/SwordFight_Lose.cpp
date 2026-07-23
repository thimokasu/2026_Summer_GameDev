#include "SwordFight_Lose.h"
#include"SwordFIghtStateHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"
#include"../../../../../Manager/Game/SE.h"


void SwordFight_Lose::EnterT(SwordFightPlayer* owner)
{
	isLoop_ = true;
	owner->GetAnimController()->Play(SwordFightPlayer::animType::Lose, false);
	SE::GetInstance().Play(SOUND_TYPE::LOSS, false);

}

void SwordFight_Lose::HandleInputT(SwordFightPlayer* owner)
{
	if (owner->GetAnimController()->IsEnd())
	{
		owner->ChangeState<SwordFight_Idle>();
	}
}

void SwordFight_Lose::UpdateT(SwordFightPlayer* owner)
{
}

void SwordFight_Lose::ExitT(SwordFightPlayer* owner)
{
}
