#include "TitleScene.h"
#include"../Manager/Game/SceneManager.h"
#include"../Manager/Generic/KeyManager.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Load(void)
{
}

void TitleScene::Init(void)
{
}

void TitleScene::Update(void)
{
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::MOUSE_LEFT).down)
	{

	SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{
}

void TitleScene::Release(void)
{
}
