#include "GameContactSystem.h"
#include"../../../Manager/Game/SceneManager.h"
#include "../../../Object/Actor/Stage/FindingJ/ReactionBlock.h"

GameContactSystem::GameContactSystem()
{
}

GameContactSystem::~GameContactSystem()
{
}

void GameContactSystem::Update(std::vector<ContactRule> contactRule )
{
	//接触開始イベントの処理
	for (auto& rule : contactRule)
	{
		Procese(rule);
	}

}

void GameContactSystem::Clear(void)
{
}

void GameContactSystem::Procese(ContactRule rule)
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
		if (eventCallback_)
		{
			eventCallback_(event.contactEvent_.entityB.entityId);
		}
		break;
	default:
		break;
	}

}

