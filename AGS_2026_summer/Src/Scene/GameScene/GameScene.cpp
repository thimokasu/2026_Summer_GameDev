#include "GameScene.h"
#include<DxLib.h>
#include <EffekseerForDXLib.h>
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

#include"Game/MiniGameHeaders.h"


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

	//プレイ人数を設定(画面分割用)
	games_.resize(SceneManager::GetInstance().GetPlayerNum(gameInfo_.game_));

	for (auto& game : games_)
	{
		game.actorMng = std::make_unique<ActorManager>();
		game.colMng = std::make_unique<CollisionManager>();
		CreateMiniGame(game,gameInfo_.game_);
		game.miniGame->Load(gameInfo_);
		game.actorMng->Load(gameInfo_);
	}


	//仮
	switch (games_.size())
	{
	case 1:
		games_[0].drawArea = { 0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y };
		break;

	case 2:
		games_[0].drawArea = { 0, 0, Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y };
		games_[1].drawArea = { Application::SCREEN_SIZE_X / 2, 0,
							   Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y };
		break;
	}
}

void GameScene::SubInit(void)
{
	for (auto& game : games_)
	{
		game.miniGame->Init();
	}

}

void GameScene::SubUpdate(void)
{
	for (auto& game : games_)
	{
		game.miniGame->Update();
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::TAB).down)
	{
		SceneManager::GetInstance().GetCamera().StopMove();
	}
}

void GameScene::SubDraw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Game");
	for (auto& game : games_)
	{
		SetDrawArea(
			game.drawArea.left,
			game.drawArea.top,
			game.drawArea.right,
			game.drawArea.bottom);
		SetCameraScreenCenter(
			(game.drawArea.left + game.drawArea.right) / 2.0f,
			(game.drawArea.top + game.drawArea.bottom) / 2.0f);

		game.miniGame->Draw();
	}

	SetDrawArea(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y);

}

void GameScene::SubRelease(void)
{
	for (auto& game : games_)
	{
		game.miniGame->Release();
	}

	games_.clear();

	SE::GetInstance().Stop(SOUND_TYPE::BGM);
	SE::GetInstance().Release();
}

void GameScene::CreateMiniGame(GameInstance& game, GAME_KIND kind)
{
	switch (kind)
	{
	case GAME_KIND::NONE:
		break;

	case GAME_KIND::TEST:
		game.miniGame = std::make_unique<TestGame>(
			game.actorMng.get(), game.colMng.get());
		break;

	case GAME_KIND::MARBLE_RACE:
		game.miniGame = std::make_unique<MarbleRace>(
			game.actorMng.get(), game.colMng.get());
		break;

	case GAME_KIND::FINDINGJ:
		game.miniGame = std::make_unique<FindingJ>(
			game.actorMng.get(), game.colMng.get());
		break;

	case GAME_KIND::FEEDJ:
		game.miniGame = std::make_unique<FeedJ>(
			game.actorMng.get(), game.colMng.get());
		break;

	case GAME_KIND::UNICYCLE:
		game.miniGame = std::make_unique<Unicycle>(
			game.actorMng.get(), game.colMng.get());
		break;

	case GAME_KIND::ATHLETIC:
		game.miniGame = std::make_unique<Athletic>(
			game.actorMng.get(), game.colMng.get());
		break;

	case GAME_KIND::SPIKE_DROP:
		game.miniGame = std::make_unique<SpikeDrop>(
			game.actorMng.get(), game.colMng.get());
		break;
	}
}

