#include "GameSelectScene.h"
#include <DxLib.h>
#include <string>
#include<memory>
#include "../../Manager/Generic/KeyManager.h"
#include"../../Manager/Resource/ResourceManager.h"
#include"../../Manager/Game/SceneManager.h"
#include"../GameScene/GameScene.h"
#define REGISTER_GAME(kind,classNamecase)GAME_KIND::kind return std::make_unique<className>()


const std::string PATH_GAMESELECTSCENE = Application::PATH_IMAGE + "GameSelectScene/";


GameSelectScene::GameSelectScene(void)
{
}

GameSelectScene::~GameSelectScene(void)
{
}

void GameSelectScene::SubLoad(void)
{
	update_ = &GameSelectScene::UpdatePlayNumSelect;
	draw_ = &GameSelectScene::DrawPlayNumSelect;
	backImage_ = LoadGraph("Data/Image/GameSelectScene/Gameselect/Test.png");
	LoadImages();
	fontHandle_ = CreateFontToHandle(NULL, 40, 5, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void GameSelectScene::SubInit(void)
{
	InitGameGroups();
}

void GameSelectScene::SubUpdate(void)
{
	(this->*update_)();
}

void GameSelectScene::SubDraw(void)
{
	(this->*draw_)();
}

void GameSelectScene::SubRelease(void)
{
	// シーン終了時に確実にクリア
	if (fontHandle_ != -1)
	{
		DeleteFontToHandle(fontHandle_);
		fontHandle_ = -1;
	}
}

void GameSelectScene::SetGameStageNum(void)
{
}

void GameSelectScene::LoadImages(void)
{
#pragma region playNum
	gameImageHandles_[GAME_KIND::ONE_PLAYER] = ResourceManager::GetInstance().Load(SRC::ONE_PLAY).handleId_;
	gameImageHandles_[GAME_KIND::TWO_PLAYER] = ResourceManager::GetInstance().Load(SRC::TWO_PLAY).handleId_;
	gameImageHandles_[GAME_KIND::TWO_VS_TWO] = ResourceManager::GetInstance().Load(SRC::TWO_VS_TWO).handleId_;
	gameImageHandles_[GAME_KIND::ONE_VS_THERR] = ResourceManager::GetInstance().Load(SRC::ONE_VS_THREE).handleId_;
	gameImageHandles_[GAME_KIND::FOUR_PLAYER] = ResourceManager::GetInstance().Load(SRC::FOUR).handleId_;
	gameImageHandles_[GAME_KIND::ONE_TO_FOUR_PLAYER] = ResourceManager::GetInstance().Load(SRC::ONE_TO_FOUR).handleId_;
#pragma endregion

#pragma region gameSelect
	gameImageHandles_[GAME_KIND::FINDINGJ] = ResourceManager::GetInstance().Load(SRC::FINDINGJ).handleId_;
	gameImageHandles_[GAME_KIND::TEST] = ResourceManager::GetInstance().Load(SRC::TEST).handleId_;
	gameImageHandles_[GAME_KIND::FEEDJ] = ResourceManager::GetInstance().Load(SRC::FEEDJ).handleId_;
	gameImageHandles_[GAME_KIND::UNICYCLE] = ResourceManager::GetInstance().Load(SRC::UNICYCLE).handleId_;
	gameImageHandles_[GAME_KIND::TEST] = LoadGraph("Data/Image/GameselectScene/GameSelect/GameTest.png");
#pragma endregion

}
void GameSelectScene::InitGameGroups(void)
{
	// テスト用のダミー割り当て (1人用、2人用にもテストデータを置いて確認できるようにします)
	onePlayerGames_ = { GAME_KIND::UNICYCLE, GAME_KIND::FINDINGJ };
	twoPlayerGames_ = {};
	oneVsThreeGames_ = {};
	twoVsTwoGames_ = {};
	fourPlayerGames_ = {  GAME_KIND::FINDINGJ };
	oneToFourPlayGames_ = {GAME_KIND::FEEDJ};

	currentGroup_ = &onePlayerGames_;
	cursorIndex_ = 0;

	if (!currentGroup_->empty())
	{
		gameInfo_.game_ = (*currentGroup_)[cursorIndex_];
	}
	else
	{
		gameInfo_.game_ = GAME_KIND::NONE;
	}
	gameInfo_.stage_ = STAGE_NUM::STAGE1;
	gameInfo_.playNum_ = PLAY_NUM::ONE_PLAYER;
}

void GameSelectScene::InitUI(void)
{
}

void GameSelectScene::InitSE(void)
{
}
void GameSelectScene::UpdatePlayNumSelect(void)
{
	const int count = static_cast<int>(PLAY_NUM::MAX);
	int currentNum = static_cast<int>(gameInfo_.playNum_);
	bool isChangedPlayNum = false;

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT_SET).down)
	{
		// 0の時に左を押すと (0 - 1 + 6) % 6 = 5 (MAX-1) になる
		currentNum = (currentNum - 1 + count) % count;
		gameInfo_.playNum_ = static_cast<PLAY_NUM>(currentNum);
		isChangedPlayNum = true;
	}
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT_SET).down)
	{
		// MAX-1 の時に右を押すと (5 + 1) % 6 = 0 に戻る
		currentNum = (currentNum + 1) % count;
		gameInfo_.playNum_ = static_cast<PLAY_NUM>(currentNum);
		isChangedPlayNum = true;
	}
	// 下キー：2ずつ進む
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_DOWN).down)
	{
		currentNum = (currentNum + 2) % count;
		gameInfo_.playNum_ = static_cast<PLAY_NUM>(currentNum);
		isChangedPlayNum = true;
	}
	// 上キー：2ずつ戻る
	else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_UP).down)
	{
		// 2引いた時にマイナスにならないよう、count を足してから剰余をとる
		currentNum = (currentNum - 2 + count) % count;
		gameInfo_.playNum_ = static_cast<PLAY_NUM>(currentNum);
		isChangedPlayNum = true;
	}

	if (isChangedPlayNum)
	{
		cursorIndex_ = 0;
		switch (gameInfo_.playNum_)
		{
		case PLAY_NUM::ONE_PLAYER:   currentGroup_ = &onePlayerGames_;   break;
		case PLAY_NUM::TWO_PLAYER:   currentGroup_ = &twoPlayerGames_;   break;
		case PLAY_NUM::ONE_VS_THERR: currentGroup_ = &oneVsThreeGames_; break;
		case PLAY_NUM::TWO_VS_TWO:   currentGroup_ = &twoVsTwoGames_;   break; // ここは構造に合わせて調整してください
		case PLAY_NUM::FOUR_PLAYER:  currentGroup_ = &fourPlayerGames_;  break;
		case PLAY_NUM::ONETOFOURPLAYER: currentGroup_ = &oneToFourPlayGames_; break;
		default:                     currentGroup_ = nullptr;            break;
		}
		if (currentGroup_ != nullptr && !currentGroup_->empty()) {
			gameInfo_.game_ = (*currentGroup_)[cursorIndex_];
		}
		else {
			gameInfo_.game_ = GAME_KIND::NONE;
		}
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::ENTER).down&&state_==SELECT_STATE::SELECTING)
	{
		state_ = SELECT_STATE::TRANSITIONING;
		transitionTimer_ = 0;
	}
	if (state_ == SELECT_STATE::TRANSITIONING)
	{
		transitionTimer_++;
		if (transitionTimer_ >= 60)
		{
			update_ = &GameSelectScene::UpdateGameSelect;
			draw_ = &GameSelectScene::DrawGameSelect;
			state_ = SELECT_STATE::SELECTING;
		}
	}
}

void GameSelectScene::UpdateGameSelect(void)
{
	if (currentGroup_ != nullptr && !currentGroup_->empty())
	{
		int size = static_cast<int>(currentGroup_->size());
		bool isChanged = false;

		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT_SET).down)
		{
			cursorIndex_ = (cursorIndex_ - 1 + size) % size;
			isChanged = true;
		}
		else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT_SET).down)
		{
			cursorIndex_ = (cursorIndex_ + 1) % size;
			isChanged = true;
		}

		if (isChanged)
		{
			gameInfo_.game_ = (*currentGroup_)[cursorIndex_];
		}
	}
	else
	{
		gameInfo_.game_ = GAME_KIND::NONE;
	}

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::ENTER).down)
	{
		state_ = SELECT_STATE::TRANSITIONING;
		transitionTimer_ = 0;
	}
	if (state_ == SELECT_STATE::TRANSITIONING)
	{
		transitionTimer_++;
		if (transitionTimer_ >= 60)
		{
			update_ = &GameSelectScene::UpdateStageSelect;
			draw_ = &GameSelectScene::DrawStageSelect;
			state_ = SELECT_STATE::SELECTING;
		}
	}
}

void GameSelectScene::UpdateStageSelect(void)
{

	//if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::LEFT).down)
	//{
	//	if (gameInfo_.stage_ > STAGE_NUM::STAGE1)
	//	{
	//		gameInfo_.stage_ = static_cast<STAGE_NUM>(static_cast<int>(gameInfo_.stage_) - 1);
	//	}
	//}
	//if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::RIGHT).down)
	//{
	//	// STAGE_NUM::MAX の手前（STAGE3）まで進める
	//	if (gameInfo_.stage_ < static_cast<STAGE_NUM>(static_cast<int>(STAGE_NUM::MAX) - 1))
	//	{
	//		gameInfo_.stage_ = static_cast<STAGE_NUM>(static_cast<int>(gameInfo_.stage_) + 1);
	//	}
	//}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT_SET).down)
	{
		if (gameInfo_.stage_ > STAGE_NUM::STAGE1)
		{
			gameInfo_.stage_ = static_cast<STAGE_NUM>(static_cast<int>(gameInfo_.stage_) - 1);
		}
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT_SET).down)
	{
		// STAGE_NUM::MAX の手前（STAGE3）まで進める
		if (gameInfo_.stage_ < static_cast<STAGE_NUM>(static_cast<int>(STAGE_NUM::MAX) - 1))
		{
			gameInfo_.stage_ = static_cast<STAGE_NUM>(static_cast<int>(gameInfo_.stage_) + 1);
		}
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::ENTER).down)

	{
		if (currentGroup_->empty())return;
		SceneManager::GetInstance().ChangeScene<GameScene>(gameInfo_);
	}
}

void GameSelectScene::DrawPlayNumSelect(void)
{
	int sizeX = Application::SCREEN_SIZE_X;
	int sizeY = Application::SCREEN_SIZE_Y;
	std::vector<Vector2F>pos;
	// 1マスあたりのサイズを算出
	float cellWidth = (float)sizeX / 5.0f;
	float cellHeight = (float)sizeY / 4.0f;
	// 4x4のグリッド位置を計算
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 5; ++x) {
			// 各マスの中心座標を求める場合
			float posX = (x * cellWidth) + (cellWidth / 2.0f);
			float posY = (y * cellHeight) + (cellHeight / 2.0f);

			pos.push_back(Vector2F(posX, posY));
		}
	}

	int displayIndices[] = { 6, 8, 11, 13, 16, 18 };

	// 順序に対応した GAME_KIND の並び順
	GAME_KIND kinds[] = {
		GAME_KIND::ONE_PLAYER, GAME_KIND::TWO_PLAYER,     // 1, 2
		GAME_KIND::ONE_VS_THERR, GAME_KIND::TWO_VS_TWO,   // 3, 4
		GAME_KIND::FOUR_PLAYER, GAME_KIND::ONE_TO_FOUR_PLAYER // 5, 6
	};
	for (int i = 0; i < 6; ++i)
	{
		int index = displayIndices[i];
		Vector2F drawPos = pos[index];
		int handle = gameImageHandles_[kinds[i]];

		float scale = 0.8f;
		if (static_cast<int>(gameInfo_.playNum_) == i)
		{
			if (state_ == SELECT_STATE::TRANSITIONING)
			{
				if (transitionTimer_ < SCALE_UP_TIME)
				{
					// 1. 押した瞬間：1.0f から 1.2f に一瞬拡大（強調）
					scale = 1.0f + (static_cast<float>(transitionTimer_) / SCALE_UP_TIME) * 0.2f;
				}
				else
				{
					// 2. そのあと：1.2f から 0.4f に沈み込むように縮小
					float progress = static_cast<float>(transitionTimer_ - SCALE_UP_TIME) / SCALE_DOWN_TIME;
					scale = 1.2f - (progress * 0.8f);
				}
			}
			else
			{
				scale = 1.0f; // 通常時
			}
		}
		if (scale <= 0)scale = 0;

		DrawRotaGraph(drawPos.x, drawPos.y - 100, scale, 0, handle, true);
	}
}

void GameSelectScene::DrawGameSelect(void)
{
	// 1. 遷移中かどうかで拡大率を決定
	float scale = 1.0f;
	if (state_ == SELECT_STATE::TRANSITIONING)
	{
		// transitionTimer_ は 0～60 なので、その進行度に合わせて拡大
		// 1.0f から 2.0f へとスムーズにズームインする例
		scale = 1.0f + (static_cast<float>(transitionTimer_) / 60.0f) * 1.0f;
	}

	// 2. 画像の描画（決定した scale を適用）
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, scale, 0, gameImageHandles_[gameInfo_.game_], true);

	// 3. ゲーム名と矢印の描画（これらはズームさせないため背景の後に描画）
	std::string gameName = gameInfo_.GetGameName();
	int textX = Application::SCREEN_SIZE_X / 2;
	int textY = Application::SCREEN_SIZE_Y / 6 * 5;

	DrawFormatStringToHandle(textX - 100, textY, GetColor(0, 0, 0), fontHandle_, "%s", gameName.c_str());

	int arrowOffset = 200;
	DrawStringToHandle(textX - arrowOffset, textY, "<-", GetColor(0, 0, 0), fontHandle_);
	DrawStringToHandle(textX + arrowOffset, textY, "->", GetColor(0, 0, 0), fontHandle_);
}
void GameSelectScene::DrawStageSelect(void)
{
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1, 0, backImage_, true);

	std::string gameName = gameInfo_.GetGameName();
	DrawStringToHandle(300, 100, gameName.c_str(), GetColor(0, 0, 0), fontHandle_);

	DrawStringToHandle(1300, 150, "操作方法", GetColor(0, 0, 0), fontHandle_);
	// フォントハンドルを使って描画
}
