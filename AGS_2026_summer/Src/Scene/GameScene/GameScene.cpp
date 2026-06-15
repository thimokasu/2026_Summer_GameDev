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
#include"../../Object/Actor/Stage/FindingJ/ReactionBlock.h"
#include"../../Object/Actor/Charactor/Player/FindingJ/FindingJCPU/FindingJRunner.h"

#include"../../Object/UI/UIBase.h"
#include"../../Object/UI/FindingJ/Timer.h"
#include"../../Object/UI/FindingJ/GameMessageUI.h"

#include"MiniGameFactoryHeaders.h"


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
	CreateMiniGame(gameInfo_.game_);
	actorMng_->Load(gameInfo_);
	miniGame_->Load();
}

void GameScene::SubInit(void)
{
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


void GameScene::CreateMiniGame(GAME_KIND kind)
{
	switch (kind)
	{
	case GAME_KIND::NONE:
		break;
	case GAME_KIND::TEST_ONE:
		break;
	case GAME_KIND::TEST_TWO:
		break;
	case GAME_KIND::TEST_THREE:
		break;
	case GAME_KIND::TEST_FOUR:
		break;
	case GAME_KIND::FINDINGJ:
		miniGameFactory_=std::make_unique<FindingJFactory>(actorMng_.get(), colMng_.get());
		break;
	}
	auto g=miniGameFactory_->CreateMiniGame();
	miniGame_ = std::move(g);
}

