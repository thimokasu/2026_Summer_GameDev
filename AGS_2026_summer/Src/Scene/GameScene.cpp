#include "GameScene.h"
#include<DxLib.h>

#include"../Manager/System/Collision/CollisionManager.h"
#include"../Manager/System/ContactSystem/ContactEventManager.h"

#include"../Object/Actor/Manager/ActorManager.h"

GameScene::GameScene(void)
{
	gameInfo_.mode_ = GameMode::TEST;
	gameInfo_.game_ = static_cast<Game>(Test::Game::A);
	gameInfo_.stageNum_ = static_cast<int>(Test::A::Stage::Stage1);
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
	actorMng_->Update();
	colMng_->Update();
	colMng_->Resolve();
	contactMng_->Update();
}

void GameScene::Draw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Game");
	actorMng_->Draw();
}

void GameScene::Release(void)
{
	actorMng_->Release();
	colMng_->ClearColliders();
}
