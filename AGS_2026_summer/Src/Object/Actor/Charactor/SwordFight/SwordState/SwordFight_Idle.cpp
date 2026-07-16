#include "SwordFight_Idle.h"
#include"SwordFIghtStateHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"

void SwordFight_Idle::EnterT(SwordFightPlayer* owner)
{
	isLoop_ = true;
	owner->GetAnimController()->Play(SwordFightPlayer::animType::Idle);

}

void SwordFight_Idle::HandleInputT(SwordFightPlayer* owner)
{
	if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FRONT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).now
		)
	{
		owner->ChangeState<SwordFIght_Walk>();
	}
}

void SwordFight_Idle::UpdateT(SwordFightPlayer* owner)
{
}

void SwordFight_Idle::ExitT(SwordFightPlayer* owner)
{
}
