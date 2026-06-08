#include "PauseScene.h"
#include<DxLib.h>
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Generic/KeyManager.h"
#include"../Manager/Game/SceneManager.h"
#include"TitleScene.h"
#include"../Manager/Game/SceneId.h"
#include<functional>

constexpr int margin_size = 150;
constexpr int expand_interval = 30;

PauseScene::PauseScene(void)
{
	update_ = &PauseScene::AppearUpdate;
	draw_ = &PauseScene::ExpandDraw;
	frame_ = 0;

	yesNoItems_ = {
		"YES",
		"NO"
	};

	menuItems_ = {
		"ゲームに戻る",
		"タイトルに戻る",
		"終了"
	};

	menuActions_["ゲームに戻る"] = [this]()
	{

		update_ = &PauseScene::DisappearUpdate;
		draw_ = &PauseScene::ExpandDraw;
	};
	menuActions_["タイトルに戻る"] = [this]()
	{

		execYesAction_ = [this]()
		{
			SceneManager::GetInstance().ResetScene(std::make_shared<TitleScene>());
		};
		yesNoTitle_ = "タイトルに戻りますか？";
		update_ = &PauseScene::YesNoUpdate;
		draw_ = &PauseScene::YesNoDraw;
	};

	menuActions_["終了"] = [this]()
	{
		execYesAction_ = [this]()
		{
			Application::GetInstance().RequestExit();
		};
		yesNoTitle_ = "ゲームを終了しますか？";
		update_ = &PauseScene::YesNoUpdate;
		draw_ = &PauseScene::YesNoDraw;
	};

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
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_UP).down)
	{
		selectedMenuIndex_ = (selectedMenuIndex_ + menuItems_.size() - 1) % menuItems_.size();
	}

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_DOWN).down)
	{
		selectedMenuIndex_ = (selectedMenuIndex_ + 1) % menuItems_.size();
	}

	if(KEY::GetIns().GetInfo(KEY::KEY_TYPE::ENTER).down)
	{
		auto menuString = menuItems_[selectedMenuIndex_];
		menuActions_[menuString]();
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
	DrawMenu();
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
		5.0f
	);
}
void PauseScene::DrawMenu()
{
	constexpr int menu_top_offset = margin_size + 600;
	constexpr int menu_left_offset = margin_size + 800;
	constexpr int menu_item_height = 80;
	constexpr uint32_t menu_item_color = 0xffffff;
	constexpr uint32_t indicator_color = 0xffaaaa;
	constexpr int menu_indent_size = 30;
	constexpr uint32_t selected_item_color = 0xffff00;
	int x = menu_left_offset;
	int y = menu_top_offset;

	for (const auto& item : menuItems_)
	{
		int x = menu_left_offset;
		auto itemColor = menu_item_color;
		if (menuItems_[selectedMenuIndex_] == item) {
			DrawString(x-30,y,"→", indicator_color);
			x += menu_indent_size;
			itemColor = selected_item_color;
		}

		DrawFormatString(x, y, itemColor,"%s" ,item.c_str());
		y += menu_item_height;
	}

}
void PauseScene::YesNoUpdate()
{
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT_SET).down || KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT_SET).down)
	{
		isYes_ = !isYes_;
	}

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::ENTER).down)
	{
		if (isYes_)
		{
			execYesAction_();
			return;
		}
		else
		{
			update_ = &PauseScene::NormalUpdate;
			draw_ = &PauseScene::NormalDraw;
		}
	}
}
void PauseScene::YesNoDraw()
{
	NormalDraw();
	const auto& wsize = Application::GetInstance().GetWindowSize();

	auto centerX = wsize.x / 2;
	auto centerY = wsize.y / 2;
	constexpr int yesno_frame_width = 300;
	constexpr int yesno_frame_height = 150;
	int top = centerY - yesno_frame_height / 2;
	int bottom = centerY + yesno_frame_height / 2;
	int left = centerX - yesno_frame_width / 2;
	int right = centerX + yesno_frame_width / 2;

	DrawBox(left, top, right, bottom, 0x000000, true);
	DrawBoxAA(left, top, right, bottom, 0xffffff, false,3.0f);

	int x = left + 50;
	int y = top + 20;
	DrawFormatString(x, y, 0xffffff, "%s", yesNoTitle_.c_str());
	y += 40;
	int idx = 0;
	if (!isYes_)
	{
		idx = 1;
	}

	for (const auto& item : yesNoItems_)
	{
		uint32_t itemColor = 0xffffff;
		if (item == yesNoItems_[idx])
		{
			DrawString(x - 30, y, "→", 0xff0000);
			itemColor = 0xff0000;
		}
		DrawFormatString(x, y, itemColor, "%s", item.c_str());
		x += 100;
	}

}

