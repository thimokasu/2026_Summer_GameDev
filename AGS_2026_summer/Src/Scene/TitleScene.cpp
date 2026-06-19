#include "TitleScene.h"
#include"../Manager/Game/SceneManager.h"
#include"../Manager/Generic/KeyManager.h"
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Resource/Resource.h"
#include"../Manager/Resource/ResourceName.h"
TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::SubLoad(void)
{
	ResourceManager& resMng = ResourceManager::GetInstance();
	 resMng.Load(SRC::TITLE).handleId_;
	resMng.Load(SRC::PUSH).handleId_;
}

void TitleScene::SubInit(void)
{
	
}

void TitleScene::SubUpdate(void)
{
	//スペース押したらゲームシーンへ
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::SPACE).down)
	{
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME_SELECT);
		return;
	}
}

void TitleScene::SubDraw(void)
{
	DrawString(0, 0, "title", 0xffffff);

	DrawGraph(0, 0, imgTitle_, TRUE);
	DrawGraph(600, 700, imgPush_, TRUE);
}

void TitleScene::SubRelease(void)
{
	DeleteGraph(imgTitle_);
	DeleteGraph(imgPush_);
}
