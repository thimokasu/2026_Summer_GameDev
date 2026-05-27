#include "GameScene.h"
#include<DxLib.h>

#include"../Manager/Game/SceneManager.h"
#include"../Manager/Generic/KeyManager.h"

#include"../Manager/System/Collision/CollisionManager.h"
#include"../Manager/System/ContactSystem/ContactEventManager.h"

#include"../Object/Actor/Manager/ActorManager.h"

GameScene::GameScene(void)
{
	gameInfo_.mode_ = GameMode::FOURPLAYER;
	gameInfo_.game_ = static_cast<Game>(FourPlayer::Game::FindingJ);
	gameInfo_.stageNum_ = static_cast<int>(FourPlayer::FindingJ::Stage::Stage3);
}

GameScene::GameScene(GameInfo info)
{
	gameInfo_ = info;
}

GameScene::~GameScene(void)
{
}

void GameScene::Load(void)
{
	actorMng_ = std::make_unique<ActorManager>();
	colMng_ = std::make_unique<CollisionManager>();
	contactMng_ = std::make_unique<ContactEventManager>();
	actorMng_->Load(gameInfo_);
}

void GameScene::Init(void)
{
	auto onBeginContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorMng_->GetEntityKind(a) };
			Entity entB{ b, actorMng_->GetEntityKind(b) };
			contactMng_->OnBeginContact(entA, entB, CollisionResult{});
		};
	auto onEndContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorMng_->GetEntityKind(a) };
			Entity entB{ b, actorMng_->GetEntityKind(b) };
			contactMng_->OnEndContact(entA, entB, CollisionResult{});
		};
	colMng_->SetContactCallbacks(onBeginContact, onEndContact);	
	SetContactEventRule();
	SetContactEventCallback();

	actorMng_->Init();
	for (auto& actor : actorMng_->GetActors())
	{
		for (const auto& [shape, collider] : actor->GetOwnColliders())
		{
			colMng_->AddCollider(collider.get(), actor->GetEntityID());
		}
	}
}

void GameScene::Update(void)
{
	////エスケープ押したらメニューシーンへ
	//if (KeyManager::GetIns().GetInfo(KEY_TYPE::PAUSE).down)
	//{
	//	isPause_ = !isPause_;
	//}

	//if (isPause_)
	//{
	//	if (pauseScene_)
	//	{
	//		pauseScene_->Update();
	//	}
	//	return;
	//}

	//スペース押したらゲームシーンへ
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::SPACE).down)
	{
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		return;
	}


	actorMng_->Update();
	colMng_->Update();
	colMng_->Resolve();
	contactMng_->Update();
}

void GameScene::Draw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Game");
	actorMng_->Draw();

	//if (isPause_)
	//{
	//	pauseScene_->Draw();
	//	return;
	//}
}

void GameScene::Release(void)
{
	actorMng_->Release();
	colMng_->ClearColliders();
}

void GameScene::SetContactEventRule(void)
{
	//イベントの発生ルールの設定
	contactMng_->SetEventRule(EntityKind::PLAYER, EntityKind::STAGE, GameEventType::TEST);
}

void GameScene::SetContactEventCallback(void)
{
	//イベントのコールバック関数の設定
	contactMng_->SetContactEventCallback(GameEventType::TEST, []() {});
}
