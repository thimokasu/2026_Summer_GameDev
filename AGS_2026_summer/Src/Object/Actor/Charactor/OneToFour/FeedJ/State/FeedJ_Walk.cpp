#include "FeedJ_Walk.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../CharactorBase.h"
#include"FeedJStateHeaders.h"
#include"../../../../Camera/Camera.h"
void FeedJ_Walk::EnterT(FeedJPlayer* owner)
{
	isLoop_ = true;

}

void FeedJ_Walk::HandleInputT(FeedJPlayer* owner)
{
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now)
	{
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::L_KEY_ACTOIN).now)
	{
		auto* dashState = dynamic_cast<FeedJ_Dash*>(owner->GetState<FeedJ_Dash>());
		dashState->SetDashVec(moveVec_);
		owner->ChangeState<FeedJ_Dash>();
	}
	else
	{
		owner->ChangeState<FeedJ_IdleState>();
	}
}

void FeedJ_Walk::UpdateT(FeedJPlayer* owner)
{
	owner->ChangeState<FeedJ_HoldState>();
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
	owner->GetTransform().pos = VAdd(owner->GetTransform().pos, VScale(moveVec, owner->GetRigidBody().GetMoveSpeed()));
}
void FeedJ_Walk::ExitT(FeedJPlayer* owner)
{
}
