#include "Character.h"
#include "../../../../Charactor/Player/Player.h"
#include "../../../../Charactor/CPU/CPU.h"
#include "../../../../Component/RigidBodyComponent/RigidBody.h"
#include "../../../../Component/PlayerInputComponent/PlayerInputComponent.h"
#include "../../../../Component/FindingJComponent/RunnerAIComponent/RunnerAIComponent.h"

Character::Character(GameInfo info)
{
	info_ = info;
}

Character::~Character()
{
}
std::vector<std::shared_ptr<ActorBase>> Character::CreateActors()
{
	std::vector<std::shared_ptr<ActorBase>>actors;

	switch (info_.gameMode)
	{
	case GAMEKMODE::OnePlayer:
		switch (static_cast<OnePlayer::Game>(info_.gameID))
		{
		case OnePlayer::Game::FindingJ:
			if (info_.stageID == 0)
			{
				//ÉvÉåÉCÉÑÅ[ÇÃçÏê¨
				auto player = std::make_shared<Player>();
				player->SetEntityKind(EntityKind::CHASER);
				player->GetTransform().pos = VGet(180.0f, 28.0f, 20.0f);
				auto rb = std::make_shared<RigidBody>();
				rb->SetBodyType(RigidBody::BodyType::DYNAMIC);
				rb->SetMoveSpeed(15);
				rb->SetJumpPower(0);
				player->AddComponent(rb);
				player->AddComponent(std::make_shared<PlayerInputComponent>(
					KEY_INPUT_W, KEY_INPUT_S,
					KEY_INPUT_A, KEY_INPUT_D,
					KEY_INPUT_Q, KEY_INPUT_E));
				player->SetEntityKind(EntityKind::CHASER);
				player->GetComponent<PlayerInputComponent>().SetJumpKey(KEY_INPUT_SPACE);
				actors.push_back(player);

				//CPU
				auto  runner = std::make_shared<CPU>();
				runner->SetEntityKind(EntityKind::RUNNER);
				runner->GetTransform().pos = VGet(180.0f, 28.0f, 182.0f);
				auto rbRunner = std::make_shared<RigidBody>();
				rbRunner->SetBodyType(RigidBody::BodyType::DYNAMIC);
				rbRunner->SetMoveSpeed(30);
				rbRunner->SetJumpPower(30);
				runner->AddComponent(rbRunner);
				runner->AddComponent(std::make_shared<RunnerAIComponent>());
				actors.push_back(runner);
			}
		}
	}


		

	return actors;
}
