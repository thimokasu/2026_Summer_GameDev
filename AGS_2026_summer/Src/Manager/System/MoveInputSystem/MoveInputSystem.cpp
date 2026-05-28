#include "MoveInputSystem.h"

#include"../../../Object/Actor/Component/PlayerInputComponent/PlayerInputComponent.h"
#include"../../../Object/Actor/Component/RigidBodyComponent/RigidBody.h"
#include"../../../Object/Actor/Component/FindingJComponent/RunnerAIComponent/RunnerAIComponent.h"
#include"../../../Object/Actor/Component/FindingJComponent/ChaserAIComponent/ChaserAIComponent.h"

#include"../../../Object/Actor/ActorBase.h"
#include"../../../Manager/Game/SceneManager.h"
#include"../../../Object/Actor/Camera/Camera.h"

MoveInputSystem::MoveInputSystem()
{
	
}

MoveInputSystem::~MoveInputSystem()
{
}
void MoveInputSystem::Update(const std::vector<std::shared_ptr<ActorBase>>& objects)
{
	//全プレイヤー（鬼）の座標をリストにまとめる
	std::vector<VECTOR> playerPositions;
	for (auto obj : objects) {
		if (obj->GetEntityKind() == EntityKind::CHASER) {
			playerPositions.push_back(obj->GetTransform().pos);
		}
	}

	for (auto obj : objects)
	{
		//プレイヤー入力コンポーネントを持っているか
		if (obj->HasComponent<PlayerInputComponent>())
		{
			auto& input = obj->GetComponent<PlayerInputComponent>();
			auto& rb = obj->GetComponent<RigidBody>();

			VECTOR moveDir = VGet(0.0f, 0.0f, 0.0f);

			//入力に応じて移動方向を設定
			if (CheckHitKey(input.frontKey_))
			{
				moveDir.z += 1.0f;
			}
			if (CheckHitKey(input.backKey_))moveDir.z -= 1.0f;
			if (CheckHitKey(input.leftKey_))moveDir.x -= 1.0f;
			if (CheckHitKey(input.rightKey_))moveDir.x += 1.0f;
			if (CheckHitKey(input.upKey_))
			{
				moveDir.y += 1.0f;
			}
			if (CheckHitKey(input.downKey_))moveDir.y -= 1.0f;
			
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
		else if (obj->HasComponent<RunnerAIComponent>())
		{
			auto& rb = obj->GetComponent<RigidBody>();
			auto& ai = obj->GetComponent<RunnerAIComponent>();
			ai.SetPos(obj->GetTransform().pos.x, obj->GetTransform().pos.z);

			//鬼の場所を教える
			ai.SetEnemyPositions(playerPositions);

			// 思考
			ai.Update();

			VECTOR targetPos = ai.GetTargetPosition();
			VECTOR moveDir = VSub(targetPos, obj->GetTransform().prevPos);
			if (VSize(moveDir) > 0.0f)
			{
				moveDir = VNorm(moveDir);
			}
			rb.AddForce(VScale(moveDir, rb.GetMoveSpeed()));
		}
		else if (obj->HasComponent<ChaserAIComponent>())
		{
			auto& rb = obj->GetComponent<RigidBody>();
			auto& ai = obj->GetComponent<ChaserAIComponent>();
			ai.SetPos(obj->GetTransform().pos.x, obj->GetTransform().pos.z);


			// 思考
			ai.Update();

			VECTOR targetPos = ai.GetTargetPosition();
			VECTOR moveDir = VSub(targetPos, obj->GetTransform().prevPos);
			if (VSize(moveDir) > 0.0f)
			{
				moveDir = VNorm(moveDir);
			}
			rb.AddForce(VScale(moveDir, rb.GetMoveSpeed()));
		}
	}

}
