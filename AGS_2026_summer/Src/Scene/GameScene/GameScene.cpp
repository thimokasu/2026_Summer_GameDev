#include "GameScene.h"
#include<DxLib.h>
#include "../../Application.h"

#include"../../Manager/Game/SceneManager.h"
#include"../../Manager/Game/UIManager.h"
#include"../../Manager/Game/SE.h"
#include"../../Manager/Resource/ResourceManager.h"
#include"../../Manager/Generic/KeyManager.h"

#include"../../Manager/System/Collision/CollisionManager.h"
#include"../../Manager/System/EventSystem/EventManager.h"
#include"../../Manager/System/EventSystem/GameEventType.h"

#include"Game/GameBase.h"

#include"../../Object/Actor/Manager/ActorManager.h"
#include"../../Object/Actor/Camera/Camera.h"
#include"../../Object/Actor/Stage/FindingJ/ReactionBlock.h"
#include"../../Object/Actor/Charactor/Player/FindingJ/FindingJCPU/FindingJRunner.h"

#include"../../Object/UI/UIBase.h"
#include"../../Object/UI/FindingJ/Timer.h"
#include"../../Object/UI/FindingJ/GameMessageUI.h"

#include <EffekseerForDXLib.h>


GameScene::GameScene(void)
{

}

GameScene::GameScene(GameInfo info)
{
	gameInfo_ = info;
}

GameScene::~GameScene(void)
{
}

void GameScene::SubLoad(void)
{
	actorMng_ = std::make_unique<ActorManager>();
	colMng_ = std::make_unique<CollisionManager>();
	actorMng_->Load(gameInfo_);
	CreateMiniGame();

	auto msgUI = std::make_shared<GameMessageUI>(Vector2F(400.0f, 200.0f), Vector2F(400.0f, 100.0f));
	msgUI->Load();
	UIManager::GetInstance().AddRootUI(msgUI);
	auto timerUI = std::make_shared<Timer>(Vector2F(50.0f, 50.0f), Vector2F(200.0f, 50.0f));
	timerUI->Load();
	timerUI->SetTimeUpCallback([this]()
		{
			EventManager::GetInstance().TriggerEvent(GameEventType::TIME_UP);
		}
	);
	UIManager::GetInstance().AddRootUI(timerUI);
	SE::GetInstance().Load(SOUND_TYPE::BGM, "Data/BGM/GameBGM.mp3");
}

void GameScene::SubInit(void)
{
	SetCollisionCollback();
	SetContactEventRule();
	SetContactEventCallback();
	
	miniGame_->Init();

	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(1.18f, 0.0f, 0.0f));
	SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(170.0f, 270.0f, 20.0f));

}

void GameScene::SubUpdate(void)
{
	miniGame_->Update();
}

void GameScene::SubDraw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Game");
	miniGame_->Draw();

}

void GameScene::SubRelease(void)
{
	miniGame_->Release();
	SE::GetInstance().Stop(SOUND_TYPE::BGM);
	SE::GetInstance().Release();
}

void GameScene::SetContactEventRule(void)
{
	//イベントの発生ルールの設定
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::REACTION_BLOCK, GameEventType::REACTION_BLOCK);
	EventManager::GetInstance().SetEventRule(EntityKind::FINDINGJ_CPU, EntityKind::REACTION_BLOCK, GameEventType::REACTION_BLOCK);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::FINDINGJ_CPU, GameEventType::HAS_CAHGHT);
}
void GameScene::SetContactEventCallback(void)
{
	//イベントのコールバック関数の設定
	EventManager::GetInstance().SetContactEventCallback(GameEventType::REACTION_BLOCK, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			if (entityKindA == EntityKind::FINDINGJ_CPU)
			{
				auto idA = rule.contactEvent_.entityA.entityID_;
				auto actor = actorMng_->FindActorByID(idA);
				auto& findingJCPU = dynamic_cast<FindingJRunner&>(*actor);
				findingJCPU.Appear();
			}
			else if (entityKindB == EntityKind::FINDINGJ_CPU)
			{
				auto idB = rule.contactEvent_.entityB.entityID_;
				auto actor = actorMng_->FindActorByID(idB);
				auto& findingJCPU = dynamic_cast<FindingJRunner&>(*actor);
				findingJCPU.Appear();
			}
		}
	);
	EventManager::GetInstance().SetContactEventCallback(GameEventType::HAS_CAHGHT, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			if (entityKindA == EntityKind::FINDINGJ_CPU)
			{
				auto idA = rule.contactEvent_.entityA.entityID_;
				auto actor = actorMng_->FindActorByID(idA);
				auto& findingJCPU = dynamic_cast<FindingJRunner&>(*actor);
				findingJCPU.SetIsDraw(true);
			}
		}
	);
}

void GameScene::SetCollisionCollback(void)
{
auto onBeginContact = [this](uint32_t a, uint32_t b)
	{
		Entity entA{ a, actorMng_->GetEntityKind(a) };
		Entity entB{ b, actorMng_->GetEntityKind(b) };
		EventManager::GetInstance().OnBeginContact(entA, entB, CollisionResult{});
	};
auto onEndContact = [this](uint32_t a, uint32_t b)
	{
		Entity entA{ a, actorMng_->GetEntityKind(a) };
		Entity entB{ b, actorMng_->GetEntityKind(b) };
		EventManager::GetInstance().OnEndContact(entA, entB, CollisionResult{});
	};
colMng_->SetContactCallbacks(onBeginContact, onEndContact);
}

void GameScene::CreateMiniGame(void)
{
	auto minigame = std::make_unique<GameBase>(gameInfo_, actorMng_.get(), colMng_.get());
	miniGame_ = std::move(minigame);
}
