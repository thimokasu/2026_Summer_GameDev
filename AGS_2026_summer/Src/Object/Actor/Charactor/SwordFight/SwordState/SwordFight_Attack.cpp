#include "SwordFight_Attack.h"
#include"SwordFIghtStateHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"

void SwordFight_Attack::EnterT(SwordFightPlayer* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFightPlayer::animType::Attack);

}

void SwordFight_Attack::HandleInputT(SwordFightPlayer* owner)
{
	if (KEY::GetIns().GetInfo(KEY_TYPE::ENTER).down)
	{

	}
	else
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
