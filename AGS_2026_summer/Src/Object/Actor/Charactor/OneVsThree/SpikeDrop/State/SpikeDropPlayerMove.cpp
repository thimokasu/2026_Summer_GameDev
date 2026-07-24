#include "SpikeDropPlayerMove.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../../Camera/Camera.h"
#include"SpikeDropPlayerJump.h"
#include"SpikeDropPlayerIdle.h"

void SpikeDropPlayerMove::EnterT(SpikeDropPlayer* owner)
{
	isLoop_ = true;

}

void SpikeDropPlayerMove::HandleInputT(SpikeDropPlayer* owner)
{
	int i = owner->GetUseController();
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE,i).down)
	{
		owner->ChangeState<SpikeDropPlayerJump>();
	}

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT,i).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT,i).now)
	{

	}
	else
	{
		owner->ChangeState<SpikeDropPlayerIdle>();
	}
}

void SpikeDropPlayerMove::UpdateT(SpikeDropPlayer* owner)
{
	VECTOR moveVec = { 0.0f,0.0f,0.0f };
	int i = owner->GetUseController();
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT,i).now) moveVec.x += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT,i).now) moveVec.x -= 1.0f;

	const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera().GetAngles();
	MATRIX camYaw = MGetRotY(cameraAngle.y);
	moveVec = VTransform(moveVec, camYaw);

	if (VSize(moveVec) > 0.0f)
	{
		moveVec = VNorm(moveVec);
	}
	float yaw = atan2f(moveVec.x, moveVec.z);
	owner->GetTransform().quaRot = Quaternion::Euler(0.0f, yaw, 0.0f);
	owner->GetTransform().pos = VAdd(owner->GetTransform().pos, VScale(moveVec, owner->GetRigidBody().GetMoveSpeed()));
}

void SpikeDropPlayerMove::ExitT(SpikeDropPlayer* owner)
{
}
