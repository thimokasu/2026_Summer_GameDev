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
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::SPACE).down)
	{

	SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{
	DrawFormatString(0, 0, 0xffffff, "title");
	DrawFormatString(100, 100, 0xffffff, "GameScene‚Å ENTER ‚ð‰Ÿ‚µ‚½‚ç“G‚Ì“§–¾‚ð‚«‚è‚©‚¦‚ê‚Ü");
}

void TitleScene::Release(void)
{
}
