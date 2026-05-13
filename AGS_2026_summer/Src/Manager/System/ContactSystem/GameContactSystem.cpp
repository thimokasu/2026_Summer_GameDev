#include "GameContactSystem.h"
#include"../../../Manager/Game/SceneManager.h"
#include "../../../Object/Actor/Component/FindingJComponent/RunnerAIComponent/RunnerAIComponent.h"

GameContactSystem::GameContactSystem()
{
}

GameContactSystem::~GameContactSystem()
{
}

void GameContactSystem::Update(std::vector<ContactRule> contactRule , const std::vector<std::shared_ptr<ActorBase>>& objects)
{
	//接触開始イベントの処理
	for (auto& rule : contactRule)
	{
		Procese(rule, objects);
	}

}

void GameContactSystem::Clear(void)
{
}

void GameContactSystem::Procese(ContactRule rule, const std::vector<std::shared_ptr<ActorBase>>& objects)
{
	//発生するイベント群を判別
	auto event = contactRuleTable_.Query(rule);


		int a = 0;
	switch (event.eventType_)
	{
	case GameEventType::NONE:
		break;
	case GameEventType::TEST:
		//SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		a = 1;
		break;
	case GameEventType::REACTION_BLOCK:
		SetColor(objects);
		break;
	default:
		break;
	}

}

void GameContactSystem::SetColor(const std::vector<std::shared_ptr<ActorBase>>& objects)
{
	for (auto obj : objects) {
		if (obj->GetEntityKind() == EntityKind::CPU)
		{
			auto& AI = obj->GetComponent<RunnerAIComponent>();

			AI.SetVisibleTime(0.1f);

		}
		

	}
}
