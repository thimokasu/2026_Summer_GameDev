#include<DxLib.h>
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Generic/KeyManager.h"
#include"../Manager/Game/SceneManager.h"
#include "TitleScene.h"
#include"../Manager/Game/SceneId.h"
TitleScene::TitleScene(void)
{
	imgPush_ = -1;
	imgTitle_ = -1;
}

TitleScene::~TitleScene(void)
{
}


void TitleScene::Init(void)
{
	imgPush_ = resMng_.LoadGraph("Date/Title/GamePick.png");
	imgTitle_ = resMng_.LoadGraph("Date/Title/title4.png");
}

void TitleScene::Update(void)
{
	//スペース押したらゲームシーンへ
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::SPACE).down)
	{
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
	}

	if (KeyManager::GetIns().GetInfo(KEY_TYPE::PAUSE).down)
	{
		SceneManager::GetInstance().ChangeScene(SCENE_ID::MENU);
	}

}

void TitleScene::Draw(void)
{
	DrawString(0, 0, "title", 0xffffff);	


	DrawGraph(0, 0, imgTitle_, TRUE);
	DrawGraph(600, 700, imgPush_, TRUE);
}
