#include "SwordFight_Attack.h"
#include"SwordFIghtStateHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"
#include"../../../../../Manager/Game/SE.h"

void SwordFight_Attack::EnterT(SwordFightPlayer* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFightPlayer::animType::Attack,false);
	SE::GetInstance().Play(SOUND_TYPE::HITATTACK, false);

}

void SwordFight_Attack::HandleInputT(SwordFightPlayer* owner)
{
	if (owner->GetAnimController()->IsEnd())
	{
		owner->ChangeState<SwordFight_Idle>();
	}
}

void SwordFight_Attack::UpdateT(SwordFightPlayer* owner)
{
}

void SwordFight_Attack::ExitT(SwordFightPlayer* owner)
{
}
