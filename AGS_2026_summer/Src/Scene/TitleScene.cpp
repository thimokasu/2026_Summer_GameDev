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
	
}

void TitleScene::SubRelease(void)
{
	DeleteGraph(imgTitle_);
	DeleteGraph(imgPush_);
}
