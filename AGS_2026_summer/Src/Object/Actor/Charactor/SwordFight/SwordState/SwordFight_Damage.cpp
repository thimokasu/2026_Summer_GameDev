#include "SwordFight_Damage.h"
#include"SwordFIghtStateHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"
#include"../../../../../Manager/Game/SE.h"


void SwordFight_Damage::EnterT(SwordFightPlayer* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFightPlayer::animType::Damage, false);
	SE::GetInstance().Play(SOUND_TYPE::CUT, false);

}

void SwordFight_Damage::HandleInputT(SwordFightPlayer* owner)
{
	if (owner->GetAnimController()->IsEnd())
	{
		owner->ChangeState<SwordFight_Idle>();
	}
}

void SwordFight_Damage::UpdateT(SwordFightPlayer* owner)
{
}

void SwordFight_Damage::ExitT(SwordFightPlayer* owner)
{
}
