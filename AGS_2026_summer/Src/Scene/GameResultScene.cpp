#include "GameResultScene.h"
#include"../Manager/Game/SceneManager.h"
#include"../Manager/Generic/KeyManager.h"
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Resource/Resource.h"
#include"../Manager/Resource/ResourceName.h"

GameResultScene::GameResultScene()
{
}

GameResultScene::~GameResultScene()
{
}

void GameResultScene::Init()
{
}

void GameResultScene::Update()
{

	//エスケープ押したらメニューシーンへ
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::PAUSE).down)
	{
		SceneManager::GetInstance().PushScene(SCENE_ID::PAUSE);
		return;
	}
}

void GameResultScene::Draw()
{
	DrawString(0, 0, "Result", 0xffffff);
}

void GameResultScene::Load(void)
{
	ResourceManager& resMng = ResourceManager::GetInstance();
}

void GameResultScene::Release(void)
{
}
