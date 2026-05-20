#include "PauseScene.h"
#include<DxLib.h>
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Generic/KeyManager.h"
#include"../Manager/Game/SceneManager.h"
#include"../Manager/Game/SceneId.h"

constexpr int margin_size = 50;

PauseScene::PauseScene(void)
{
}

PauseScene::~PauseScene(void)
{
}

void PauseScene::Init(void) 
{
	
}

void PauseScene::Update(void)
{
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::PAUSE).down)
	{
		auto scene = SceneManager::GetInstance().GetNowScene();

		if (scene == SCENE_ID::GAME)
		{
			SceneManager::GetInstance().ChangeScene(SCENE_ID::PAUSE);
		}
		else if (scene == SCENE_ID::PAUSE)
		{
			SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
		}

	}
		
		
	
}

void PauseScene::Draw(void)
{
	const auto& wsize = Application::GetInstance().GetWindowSize();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 168);
	
	DrawBoxAA(margin_size, margin_size, wsize.x - margin_size, wsize.y - margin_size, 0xffffff, true, 1.0f);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawString(0, 0, "pause", 0xffffff);
}
