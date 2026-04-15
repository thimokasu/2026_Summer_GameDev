#include "TitleScene.h"
#include"../Manager/Game/SceneManager.h"

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
	SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
}

void TitleScene::Draw(void)
{
}

void TitleScene::Release(void)
{
}
