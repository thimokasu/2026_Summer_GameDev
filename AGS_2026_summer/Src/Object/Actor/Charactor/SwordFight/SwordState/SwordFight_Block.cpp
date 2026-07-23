#include "SwordFight_Block.h"
#include"SwordFIghtStateHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../CharactorBase.h"
#include"../../../../Common/AnimationController.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"
#include"../../../../../Manager/Game/SE.h"

void SwordFight_Block::EnterT(SwordFightPlayer* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFightPlayer::animType::Block, false);
	SE::GetInstance().Play(SOUND_TYPE::HITSWORD, false);

}

void SwordFight_Block::HandleInputT(SwordFightPlayer* owner)
{
		if (owner->GetAnimController()->IsEnd())
		{
			owner->ChangeState<SwordFight_BlockIdle>();
		}
}

void SwordFight_Block::UpdateT(SwordFightPlayer* owner)
{
}

void SwordFight_Block::ExitT(SwordFightPlayer* owner)
{
}
