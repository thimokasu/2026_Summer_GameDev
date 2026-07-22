#include "DropperIdle.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../../Camera/Camera.h"
#include"DropperDrop.h"
#include "DropperMove.h"

void DropperIdle::EnterT(Dropper* owner)
{
	isLoop_ = true;
}

void DropperIdle::HandleInputT(Dropper* owner)
{
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now)
	{
		owner->ChangeState<DropperMove>();
	}
	if(KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
	{
		owner->ChangeState<DropperDrop>();
	}
}

void DropperIdle::UpdateT(Dropper* owner)
{
}

void DropperIdle::ExitT(Dropper* owner)
{
}
