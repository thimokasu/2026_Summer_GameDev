#include "GameScene.h"
#include<DxLib.h>

#include"../Manager/System/Collision/CollisionManager.h"

#include"../Object/Actor/Manager/ActorManager.h"

GameScene::GameScene(void)
{
	gameInfo_.mode_ = GameMode::FOURPLAYER;
	gameInfo_.game_ = static_cast<Game>(FourPlayer::Game::A);
	gameInfo_.stageNum_ = static_cast<int>(FourPlayer::A::Stage::Stage1);
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

	actorMng_->Load(gameInfo_);
}

void GameScene::Init(void)
{
	actorMng_->Init();
}

void GameScene::Update(void)
{
	actorMng_->Update();
	colMng_->Update();
}

void GameScene::Draw(void)
{
	DrawString(0, 0, "game", 0xffffff);
	actorMng_->Draw();
}

void GameScene::Release(void)
{
	actorMng_->Release();
	colMng_->ClearColliders();
}
