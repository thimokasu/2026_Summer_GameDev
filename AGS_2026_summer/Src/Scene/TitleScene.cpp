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
	imgPush_ = resMng_.LoadGraph("Resources/Texture/Title/push.png");
	imgTitle_ = resMng_.LoadGraph("Resources/Texture/Title/title.png");
}

void TitleScene::Update(void)
{
	//スペース押したらゲームシーンへ
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::SPACE).down)
	{
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{
	
}
