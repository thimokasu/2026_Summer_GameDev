#include "FeedJ_HoldWalk.h"
#include"../../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../CharactorBase.h"
#include"FeedJStateHeaders.h"
#include"../../../../Camera/Camera.h"
#include"../../../../Item/ItemBase.h"
#include"../../../../Item/FeedJ/FeedJItemHeaders.h"
void FeedJ_HoldWalk::EnterT(FeedJPlayer* owner)
{
	isLoop_ = true;
}

void FeedJ_HoldWalk::HandleInputT(FeedJPlayer* owner)
{	
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::L_KEY_ACTOIN).down)
	{
		auto* dashState = dynamic_cast<FeedJ_Dash*>(owner->GetState<FeedJ_Dash>());
		dashState->SetDashVec(moveVec_);
		owner->ChangeState<FeedJ_Dash>();
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION).down)
	{
		auto item = owner->GetHoldItem();
		if (auto food = dynamic_cast<FoodBase*>(item))
		{
			food->Detach();
			food->Drop(owner);
		}
		else if (auto continer = dynamic_cast<ContainerBase*>(item))
		{

		}
		owner->ReleaseHoldItem();
		owner->ChangeState<FeedJ_IdleState>();
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::K_KEY_ACTION).down)
	{
		auto* item = owner->GetHoldItem();
		if (auto food = dynamic_cast<FoodBase*>(item))
		{
			food->Detach();
			food->Throw(owner);
		}
		owner->ReleaseHoldItem();
		owner->ChangeState<FeedJ_IdleState>();
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now ||
		KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now)
	{
	}
	else
	{
		owner->ChangeState<FeedJ_HoldState>();
	}

}

void FeedJ_HoldWalk::UpdateT(FeedJPlayer* owner)
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

void FeedJ_HoldWalk::ExitT(FeedJPlayer* owner)
{
}
