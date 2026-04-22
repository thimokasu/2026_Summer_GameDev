#include "MoveInputSystem.h"

#include"../../../Object/Actor/Component/PlayerInputComponent/PlayerInputComponent.h"
#include"../../../Object/Actor/Component/RigidBodyComponent/RigidBody.h"

#include"../../../Object/Actor/ActorBase.h"
#include"../../../Manager/Game/SceneManager.h"
#include"../../../Object/Actor/Camera/Camera.h"

#include "../../../Net/NetManager.h"
#include "../../../Net/NetStructures.h"

#include "../../../Object/Actor/Component/NetPlayerIDComponent/NetPlayerIDComponent.h"

MoveInputSystem::MoveInputSystem()
{
}

MoveInputSystem::~MoveInputSystem()
{
}
void MoveInputSystem::Update(const std::vector<std::shared_ptr<ActorBase>>& objects)
{

	bool isAction = false;
	auto& nIns = NetManager::GetInstance();

	using PID = NetPlayerIDComponent;
	using PAction= PLAYER_ACTION;

	for (auto obj : objects)
	{
		//プレイヤー入力コンポーネントを持っているか
		if (obj->HasComponent<PlayerInputComponent>())
		{
			auto& input = obj->GetComponent<PlayerInputComponent>();
			auto& rb = obj->GetComponent<RigidBody>();

			VECTOR moveDir = VGet(0.0f, 0.0f, 0.0f);

			isAction = CheckHitKey(input.frontKey_);
			//入力に応じて移動方向を設定
			if (nIns.IsAction(
				obj->GetComponent<PID>().GetUserId(),
				PAction::MOVE_FORWARD,isAction))
			{
				moveDir.z += 1.0f;
				if (obj->GetComponent<PID>().GetUserId() == nIns.GetSelf().key)
				{
					nIns.SetAction(PAction::MOVE_FORWARD);
				}
			}
			isAction = CheckHitKey(input.backKey_);
			if (nIns.IsAction(
				obj->GetComponent<PID>().GetUserId(),
				PAction::MOVE_BACK,isAction))
			{
				moveDir.z -= 1.0f;
				if (obj->GetComponent<PID>().GetUserId() == nIns.GetSelf().key)
				{
					nIns.SetAction(PAction::MOVE_BACK);
				}
			}
			isAction = CheckHitKey(input.leftKey_);
			if (nIns.IsAction(
				obj->GetComponent<PID>().GetUserId(),
				PAction::MOVE_LEFT,isAction))
			{
				moveDir.y += 1.0f;
				if (obj->GetComponent<PID>().GetUserId() == nIns.GetSelf().key)
				{
					nIns.SetAction(PAction::MOVE_LEFT);
				}
			}
			isAction = CheckHitKey(input.rightKey_);
			if (nIns.IsAction(
				obj->GetComponent<PID>().GetUserId(),
				PAction::MOVE_RIGHT,isAction))
			{
				moveDir.y -= 1.0f;
				if (obj->GetComponent<PID>().GetUserId() == nIns.GetSelf().key)
				{
					nIns.SetAction(PAction::MOVE_RIGHT);
				}
			}
			
			const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera()->GetAngles();
			MATRIX camYaw = MGetRotY(cameraAngle.y);
			moveDir = VTransform(moveDir, camYaw);

			if (VSize(moveDir) > 0.0f)
			{
				moveDir = VNorm(moveDir);
			}

			if (CheckHitKey(input.jumpKey_))
			{
				rb.SetVelocity(VAdd(rb.GetVelocity(), VGet(0, rb.GetJumpPower(), 0)));
			}
			
			rb.AddForce(VScale(moveDir, rb.GetMoveSpeed()));

		}
	}

}
