#include "PauseScene.h"
#include<DxLib.h>
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Generic/KeyManager.h"
#include"../Manager/Game/SceneManager.h"
#include"../Manager/Game/SceneId.h"

constexpr int margin_size = 150;
constexpr int expand_interval = 30;

PauseScene::PauseScene(void)
{
	update_ = &PauseScene::AppearUpdate;
	draw_ = &PauseScene::ExpandDraw;
	frame_ = 0;
}

PauseScene::~PauseScene(void)
{
}

void PauseScene::Init(void) 
{
	
}

void PauseScene::Update(void)
{
	(this->*update_)();
}

void PauseScene::Draw(void)
{
	(this->*draw_)();
}

void PauseScene::AppearUpdate()
{
	if(++frame_ >= expand_interval)
	{
		update_ = &PauseScene::NormalUpdate;
		draw_ = &PauseScene::NormalDraw;
		return;	
	}
}

void PauseScene::NormalUpdate()
{

	if(KEY::GetIns().GetInfo(KEY::KEY_TYPE::PAUSE).down)
	{
		update_ = &PauseScene::DisappearUpdate;
		draw_ = &PauseScene::ExpandDraw;
		return;
	}
}

void PauseScene::DisappearUpdate()
{
	if (--frame_ <= 0)
	{
		SceneManager::GetInstance().PopScene();
		return;
	}
}

void PauseScene::ExpandDraw()
{
	DrawFrame(static_cast<float>(frame_) / static_cast<float>(expand_interval));
}

void PauseScene::NormalDraw()
{
	DrawFrame(1.0f);
	DrawString(Application::SCREEN_SIZE_X / 2 - 100, Application::SCREEN_SIZE_Y / 2 - 50, "PAUSE", 0xffffff);
}

void PauseScene::DrawFrame(float rate)
{
	const auto& wsize = Application::GetInstance().GetWindowSize();

	const auto centerY = wsize.y / 2;
	auto height = (wsize.y - margin_size) / 2;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 168);

	DrawBoxAA(
		margin_size,
		centerY - height * rate,
		wsize.x - margin_size,
		centerY + height * rate,
		0xffffff,
		true,
		1.0f
	);
	//必ず元の設定（ノーマル）にリセットする！
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawBoxAA(margin_size,
		centerY - height * rate,
		wsize.x - margin_size,
		centerY + height * rate,
		0x000000,
		false,
		1.0f
	);
}
