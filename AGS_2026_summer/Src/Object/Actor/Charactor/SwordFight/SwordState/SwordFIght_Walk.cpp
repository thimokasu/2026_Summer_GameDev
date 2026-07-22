#include "SwordFIght_Walk.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"SwordFIghtStateHeaders.h"
#include"../../CharactorBase.h"
#include"../../../Camera/Camera.h"
#include"../../../../Common/AnimationController.h"
void SwordFIght_Walk::EnterT(SwordFightPlayer* owner)
{
	isLoop_ = true;

	owner->GetAnimController()->Play(SwordFightPlayer::animType::Walk);

	printfDx("Walk Enter\n");
}

void SwordFIght_Walk::HandleInputT(SwordFightPlayer* owner)
{
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now)
	{
	}
	else
	{
		owner->ChangeState<SwordFight_Idle>();
	}

	if (KEY::GetIns().GetInfo(KEY_TYPE::ENTER).down)
	{
		owner->ChangeState<SwordFight_Attack>();
	}

	if (KEY::GetIns().GetInfo(KEY_TYPE::TAB).down)
	{
		owner->ChangeState<SwordFight_BlockIdle>();
	}

	if (KEY::GetIns().GetInfo(KEY_TYPE::SPACE).down)
	{
		owner->ChangeState<SwordFight_Lose>();
	}

	if (KEY::GetIns().GetInfo(KEY_TYPE::SHIFT).down)
	{
		owner->ChangeState<SwordFight_Damage>();
	}
}

void SwordFIght_Walk::UpdateT(SwordFightPlayer* owner)
{
	VECTOR moveVec = { 0.0f,0.0f,0.0f };

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now) moveVec.z += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now) moveVec.z -= 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now) moveVec.x += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now) moveVec.x -= 1.0f;

	const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera().GetAngles();
	MATRIX camYaw = MGetRotY(cameraAngle.y);
	moveVec = VTransform(moveVec, camYaw);

	if (VSize(moveVec) > 0.0f)
	{
		moveVec = VNorm(moveVec);
	}
	moveVec_ = moveVec;
	float yaw = atan2f(moveVec.x, moveVec.z);
	owner->GetTransform().quaRot = Quaternion::Euler(0.0f, yaw, 0.0f);
	owner->GetTransform().pos = VAdd(owner->GetTransform().pos, VScale(moveVec, owner->GetRigidBody().GetMoveSpeed()));
}

void SwordFIght_Walk::ExitT(SwordFightPlayer* owner)
{
}
