#include "DropperMove.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../CharactorBase.h"
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../../Camera/Camera.h"
#include"DropperDrop.h"
#include"DropperIdle.h"

void DropperMove::EnterT(Dropper* owner)
{
	isLoop_ = true;

}

void DropperMove::HandleInputT(Dropper* owner)
{
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
	{
		owner->ChangeState<DropperDrop>();
	}

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now)
	{

	}
	else
	{
		owner->ChangeState<DropperIdle>();
	}
}

void DropperMove::UpdateT(Dropper* owner)
{

	VECTOR moveVec = { 0.0f,0.0f,0.0f };

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now) moveVec.x += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now) moveVec.x -= 1.0f;

	const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera().GetAngles();
	MATRIX camYaw = MGetRotY(cameraAngle.y);
	moveVec = VTransform(moveVec, camYaw);

	if (VSize(moveVec) > 0.0f)
	{
		moveVec = VNorm(moveVec);
	}
	float yaw = atan2f(moveVec.x, moveVec.z);
	owner->GetTransform().pos = VAdd(owner->GetTransform().pos, VScale(moveVec, owner->GetRigidBody().GetMoveSpeed()));
}

void DropperMove::ExitT(Dropper* owner)
{
}
