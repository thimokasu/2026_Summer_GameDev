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
}

void PauseScene::Draw(void)
{
	const auto& wsize = Application::GetInstance().GetWindowSize();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 168);
	
	DrawBoxAA(margin_size, margin_size, wsize.x - margin_size, wsize.y - margin_size, 0xffffff, true, 1.0f);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawString(0, 0, "pause", 0xffffff);
}

void PauseScene::AppearUpdate()
{
}

void PauseScene::NormalUpdate()
{
}

void PauseScene::DisappearUpdate()
{
}

void PauseScene::ExpandDraw()
{
}

void PauseScene::NormalDraw()
{
}

void PauseScene::DrawFrame()
{
}
