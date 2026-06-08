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

void TitleScene::Load(void)
{
	ResourceManager& resMng = ResourceManager::GetInstance();
	imgTitle_ = resMng.Load(SRC::TITLE).handleId_;
	imgPush_ = resMng.Load(SRC::PUSH).handleId_;
}

void TitleScene::Init(void)
{
	
}

void TitleScene::Update(void)
{
	//エスケープ押したらメニューシーンへ
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::PAUSE).down)
	{
		SceneManager::GetInstance().PushScene(SCENE_ID::PAUSE);
		return;
	}

	

	//スペース押したらゲームシーンへ
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::SPACE).down)
	{
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
		return;
	}
}

void TitleScene::Draw(void)
{
	DrawString(0, 0, "title", 0xffffff);


	DrawGraph(0, 0, imgTitle_, TRUE);
	DrawGraph(600, 700, imgPush_, TRUE);

	
}

void TitleScene::Release(void)
{
}
