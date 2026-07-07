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

	//YES or NOの選択肢は共通なので、コンストラクタで初期化しておく
	yesNoItems_ = {
		"YES",
		"NO"
	};

	//メニューの内容と、選択したときのアクションを定義する
	menuItems_ = {
		"ゲームに戻る",
		"タイトルに戻る",
		"終了"
	};

	//ラムダ式でアクションを定義する
	menuActions_["ゲームに戻る"] = [this]()
		{

			update_ = &PauseScene::DisappearUpdate;
			draw_ = &PauseScene::ExpandDraw;
		};

	//ラムダ式の中でさらにラムダ式を定義している。YESを選択したときのアクションを定義している。
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

void PauseScene::SubInit(void) 
{

}

void PauseScene::SubUpdate(void)
{
	//関数ポインタを呼び出す
	(this->*update_)();
}

void PauseScene::SubDraw(void)
{
	//関数ポインタを呼び出す
	(this->*draw_)();
}

void PauseScene::AppearUpdate()
{
	//フレームが一定数を超えたら、通常の更新と描画に切り替える
	if (++frame_ >= expand_interval)
	{
		update_ = &PauseScene::NormalUpdate;
		draw_ = &PauseScene::NormalDraw;
		return;
	}
}

void PauseScene::NormalUpdate()
{
	//PAUSEキーが押されたら、フェードアウトしてシーンを切り替える
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::PAUSE).down)
	{
		update_ = &PauseScene::DisappearUpdate;
		draw_ = &PauseScene::ExpandDraw;
		return;
	}

	//上キーでメニューの選択肢を上に、下キーで下に移動する
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_UP).down)
	{
		selectedMenuIndex_ = (selectedMenuIndex_ + menuItems_.size() - 1) % menuItems_.size();
	}

	//下キーでメニューの選択肢を下に移動する
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_DOWN).down)
	{
		selectedMenuIndex_ = (selectedMenuIndex_ + 1) % menuItems_.size();
	}

	//エンターキーが押されたら、選択されているメニューのアクションを実行する
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::ENTER).down)
	{
		auto menuString = menuItems_[selectedMenuIndex_];
		menuActions_[menuString]();
	}
}

void PauseScene::DisappearUpdate()
{
	//フレームが一定数を超えたら、シーンを切り替える
	if (--frame_ <= 0)
	{
		SceneManager::GetInstance().PopScene();
		return;
	}
}

void PauseScene::ExpandDraw()
{
	//フレームの進行に応じて、フェードイン・フェードアウトのエフェクトを描画する
	DrawFrame(static_cast<float>(frame_) / static_cast<float>(expand_interval));
}

void PauseScene::NormalDraw()
{
	//背景を暗くする
	DrawFrame(1.0f);
	DrawMenu();
}

void PauseScene::DrawFrame(float rate)
{
	//ウィンドウサイズを取得する
	const auto& wsize = Application::GetInstance().GetWindowSize();

	//画面の中心を計算する
	const auto centerY = wsize.y / 2;
	auto height = (wsize.y - margin_size) / 2;

	//半透明の白い四角形を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 168);

	//四角形を描画する。rateの値に応じて、四角形の高さを変化させることで、フェードイン・フェードアウトのエフェクトを表現する
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

	//四角形の枠線を描画する。こちらもrateの値に応じて高さを変化させる
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
	//メニューの描画位置や、アイテムの高さ、色などを定数で定義する
	constexpr int menu_top_offset = Application::SCREEN_SIZE_Y / 2;
	constexpr int menu_left_offset = Application::SCREEN_SIZE_X / 2;
	constexpr int menu_item_height = 80;
	constexpr uint32_t menu_item_color = 0xffffff;
	constexpr uint32_t indicator_color = 0xffaaaa;
	constexpr int menu_indent_size = 30;
	constexpr uint32_t selected_item_color = 0xffff00;
	int x = menu_left_offset;
	int y = menu_top_offset;

	//メニューアイテムを描画する。選択されているアイテムには矢印を描画し、色を変える
	for (const auto& item : menuItems_)
	{
		//選択されているアイテムには矢印を描画し、色を変える
		int x = menu_left_offset;
		auto itemColor = menu_item_color;
		if (menuItems_[selectedMenuIndex_] == item) {
			DrawString(x - 30, y, "→", indicator_color);
			x += menu_indent_size;
			itemColor = selected_item_color;
		}

		//アイテムの文字列を描画する
		DrawFormatString(x, y, itemColor, "%s", item.c_str());
		y += menu_item_height;
	}

}
void PauseScene::YesNoUpdate()
{
	//左右キーでYESとNOを切り替える
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT_SET).down || KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT_SET).down)
	{
		isYes_ = !isYes_;
	}

	//エンターキーが押されたら、YESかNOの選択肢に応じてアクションを実行するか、通常のメニューに戻る
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
	//YES/NOの選択肢を描画する
	NormalDraw();
	const auto& wsize = Application::GetInstance().GetWindowSize();

	//画面の中心を計算する
	auto centerX = wsize.x / 2;
	auto centerY = wsize.y / 2;
	constexpr int yesno_frame_width = 300;
	constexpr int yesno_frame_height = 150;
	int top = centerY - yesno_frame_height / 2;
	int bottom = centerY + yesno_frame_height / 2;
	int left = centerX - yesno_frame_width / 2;
	int right = centerX + yesno_frame_width / 2;

	//半透明の白い四角形を描画する
	DrawBox(left, top, right, bottom, 0x000000, true);
	//四角形の枠線を描画する
	DrawBoxAA(left, top, right, bottom, 0xffffff, false, 3.0f);

	//YES/NOのタイトルを描画する
	int x = left + 50;
	int y = top + 20;
	//YES/NOのタイトルを描画する
	DrawFormatString(x, y, 0xffffff, "%s", yesNoTitle_.c_str());
	y += 40;
	int idx = 0;
	if (!isYes_)
	{
		idx = 1;
	}

	//YES/NOの選択肢を描画する。選択されているアイテムには矢印を描画し、色を変える
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
