#include "MarbleRaceMove.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../../Camera/Camera.h"
#include"MarbleRaveAttack.h"
#include"MarbleRaceIdle.h"
#include"MarbleRaceHit.h"
#include"../../../../../Common/AnimationController.h"
void MarbleRaceMove::EnterT(MarbleRacePlayer* owner)
{
	stateFrame_ = 0;
	isLoop_ = true;
	auto anim=owner->GetAnimController();
	anim->Play(0);
}

void MarbleRaceMove::HandleInputT(MarbleRacePlayer* owner)
{
	int i=owner->GetUseController();
	if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FRONT, i).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT, i).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK, i).now ||
		KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT, i).now
		)
	{
	}
	else {
		owner->ChangeState<MarbleRaceIdle>();
	}
	
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION,i).down)
	{
		owner->ChangeState<MarbleRaceAttack>();
	}

}

void MarbleRaceMove::UpdateT(MarbleRacePlayer* owner)
{

	VECTOR moveVec = { 0.0f,0.0f,0.0f };
	int i = owner->GetUseController();
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT,i).now) {
		moveVec.z += 1.0f;
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK,i).now) moveVec.z -= 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT,i).now) moveVec.x += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT,i).now) moveVec.x -= 1.0f;

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

void MarbleRaceMove::ExitT(MarbleRacePlayer* owner)
{
}
