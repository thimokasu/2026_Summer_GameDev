#include "GameSelectScene.h"
#include <DxLib.h>
#include <string>
#include<memory>
#include "../../Manager/Generic/KeyManager.h"
#include"../../Manager/Game/SceneManager.h"
#include"../GameScene/GameScene.h"
#define REGISTER_GAME(kind,classNamecase)GAME_KIND::kind return std::make_unique<className>()

GameSelectScene::GameSelectScene(void)
{
}

GameSelectScene::~GameSelectScene(void)
{
}

void GameSelectScene::SubLoad(void)
{
}

void GameSelectScene::SubInit(void)
{
	InitGameGroups();
}

void GameSelectScene::SubUpdate(void)
{
	// 現在の状態に応じて、呼ぶ更新関数を切り替える
	switch (state_)
	{
	case SELECT_STATE::SELECT_PLAYER_NUM:
		// 【右キー または スペース】人数を確定してゲーム選択へ
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::B).down ||
			KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
		{
			if (currentGroup_ != nullptr && !currentGroup_->empty())
			{
				state_ = SELECT_STATE::SELECT_GAME;
				cursorIndex_ = 0; // ゲーム選択のカーソルをリセット
				gameInfo_.game_ = (*currentGroup_)[cursorIndex_];
			}
		}
		else
		{
			// 進むキーが押されていない時だけ、左右の人数切り替えを行う
			UpdatePlayerNumLeftRight();
		}
		break;

	case SELECT_STATE::SELECT_GAME:
		// 【下キー】人数選択（一つ前）に戻る
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::A).down ||
			KEY::GetIns().GetInfo(KEY::KEY_TYPE::UP).down)
		{
			state_ = SELECT_STATE::SELECT_PLAYER_NUM;
		}
		// 【右キー または スペース】ゲームを確定してステージ選択へ
		else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::B).down ||
			KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
		{
			state_ = SELECT_STATE::SELECT_STAGE;
		}
		else
		{
			// 戻る・進むキーが押されていない時だけ、左右のゲーム切り替えを行う
			UpdateCursorIndex();
		}
		break;

	case SELECT_STATE::SELECT_STAGE:
		// 【下キー】ゲーム選択（一つ前）に戻る
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::A).down ||
			KEY::GetIns().GetInfo(KEY::KEY_TYPE::UP).down)
		{
			state_ = SELECT_STATE::SELECT_GAME;
		}
		// 【右キー または スペース】ステージを確定してGameSceneへ遷移！
		else if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::B).down ||
			KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
		{
			SceneManager::GetInstance().ChangeScene<GameScene>(gameInfo_);
		}
		else
		{
			// 戻る・進むキーが押されていない時だけ、左右のステージ切り替えを行う
			UpdateStageSelect();
		}
		break;
	}
}

void GameSelectScene::SubDraw(void)
{
	// ========================================================
	// 1. カラー定義 (画像の色合い)
	// ========================================================
	unsigned int colorLineBlue = GetColor(45, 95, 160); // 紺色の枠線
	unsigned int colorFillRed = GetColor(255, 0, 0); // 選択中タブの赤
	unsigned int colorWhite = GetColor(255, 255, 255); // 白
	unsigned int colorBlack = GetColor(0, 0, 0); // 黒
	unsigned int colorSelectEdge = GetColor(255, 200, 0); // 選択中の強調色
	unsigned int colorGray = GetColor(128, 128, 128); // ガイド用のグレー

	// ========================================================
	// 2. 上部：プレイ人数タブの描画 (左右で選択)
	// ========================================================
	int tabWidth = 160;
	int tabHeight = 50;
	int tabStartX = 140;
	int tabStartY = 40;

	const char* tabLabels[] = { "1人", "２人", "３人", "４人" };

	int currentPlayNumIdx = 0;
	switch (gameInfo_.playNum_)
	{
	case PLAY_NUM::ONE_PLAYER:   currentPlayNumIdx = 0; break;
	case PLAY_NUM::TWO_PLAYER:   currentPlayNumIdx = 1; break;
	case PLAY_NUM::ONE_VS_THERR: currentPlayNumIdx = 2; break;
	case PLAY_NUM::TWO_VS_TWO:   currentPlayNumIdx = 2; break;
	case PLAY_NUM::FOUR_PLAYER:  currentPlayNumIdx = 3; break;
	}

	for (int i = 0; i < 4; ++i)
	{
		int x1 = tabStartX + (i * tabWidth);
		int y1 = tabStartY;
		int x2 = x1 + tabWidth;
		int y2 = y1 + tabHeight;

		// 人数選択モードかつ、現在のタブなら赤
		if (i == currentPlayNumIdx && state_ == SELECT_STATE::SELECT_PLAYER_NUM)
		{
			DrawBox(x1, y1, x2, y2, colorFillRed, TRUE);
			DrawBox(x1, y1, x2, y2, colorLineBlue, FALSE);
			DrawString(x1 + 60, y1 + 18, tabLabels[i], colorWhite);
		}
		// ゲーム選択中などで、選ばれている人数タブ
		else if (i == currentPlayNumIdx)
		{
			DrawBox(x1, y1, x2, y2, colorFillRed, TRUE);
			DrawBox(x1, y1, x2, y2, colorLineBlue, FALSE);
			DrawString(x1 + 60, y1 + 18, tabLabels[i], colorBlack);
		}
		else
		{
			DrawBox(x1, y1, x2, y2, colorWhite, TRUE);
			DrawBox(x1, y1, x2, y2, colorLineBlue, FALSE);
			DrawString(x1 + 60, y1 + 18, tabLabels[i], colorBlack);
		}
	}

	// ========================================================
	// 3. 下部：ゲームリストの大枠
	// ========================================================
	int mainBoxX1 = 70;
	int mainBoxY1 = tabStartY + tabHeight;
	int mainBoxX2 = mainBoxX1 + (tabWidth * 4) + 140;
	int mainBoxY2 = mainBoxY1 + 340;

	// 背景白、枠線紺色
	DrawBox(mainBoxX1, mainBoxY1, mainBoxX2, mainBoxY2, colorWhite, TRUE);
	DrawBox(mainBoxX1, mainBoxY1, mainBoxX2, mainBoxY2, colorLineBlue, FALSE);

	// ========================================================
	// 4. 横並びの大きな3つのゲーム枠を描画
	// ========================================================
	// 中央の大きな枠の座標
	int centerWidth = 340;
	int centerHeight = 260;
	int centerX1 = (mainBoxX1 + mainBoxX2) / 2 - (centerWidth / 2);
	int centerY1 = mainBoxY1 + 40;
	int centerX2 = centerX1 + centerWidth;
	int centerY2 = centerY1 + centerHeight;

	// 左側の枠の座標
	int sideWidth = 180;
	int sideHeight = 260;
	int leftX1 = mainBoxX1 + 30;
	int leftY1 = centerY1;
	int leftX2 = leftX1 + sideWidth;
	int leftY2 = leftY1 + sideHeight;

	// 右側の枠の座標
	int rightX2 = mainBoxX2 - 30;
	int rightY1 = centerY1;
	int rightX1 = rightX2 - sideWidth;
	int rightY2 = rightY1 + sideHeight;

	// 各枠を描画
	DrawBox(leftX1, leftY1, leftX2, leftY2, colorLineBlue, FALSE);
	DrawBox(centerX1, centerY1, centerX2, centerY2, colorLineBlue, FALSE);
	DrawBox(rightX1, rightY1, rightX2, rightY2, colorLineBlue, FALSE);

	// ゲーム選択中なら中央の枠を黄色（または赤）で強調
	if (state_ == SELECT_STATE::SELECT_GAME)
	{
		DrawBox(centerX1 - 3, centerY1 - 3, centerX2 + 3, centerY2 + 3, colorSelectEdge, FALSE);
	}

	// ========================================================
	// 5. 枠の中にゲーム名を表示するロジック
	// ========================================================
	int totalGames = currentGroup_ ? static_cast<int>(currentGroup_->size()) : 0;

	if (totalGames > 0)
	{
		// ① 中央（現在選択中：cursorIndex_）
		GameInfo centerInfo;
		centerInfo.game_ = (*currentGroup_)[cursorIndex_];
		DrawString(centerX1 + 40, centerY1 + (centerHeight / 2) - 10, centerInfo.GetGameName().c_str(), colorBlack);

		// ② 左側（1つ前のゲーム：cursorIndex_ - 1 があれば表示）
		if (cursorIndex_ > 0)
		{
			GameInfo leftInfo;
			leftInfo.game_ = (*currentGroup_)[cursorIndex_ - 1];
			DrawString(leftX1 + 20, leftY1 + (sideHeight / 2) - 10, leftInfo.GetGameName().c_str(), colorBlack);
		}

		// ③ 右側（1つ次のゲーム：cursorIndex_ + 1 があれば表示）
		if (cursorIndex_ + 1 < totalGames)
		{
			GameInfo rightInfo;
			rightInfo.game_ = (*currentGroup_)[cursorIndex_ + 1];
			DrawString(rightX1 + 20, rightY1 + (sideHeight / 2) - 10, rightInfo.GetGameName().c_str(), colorBlack);
		}
	}
	else
	{
		DrawString(centerX1 + 120, centerY1 + (centerHeight / 2) - 10, "No Game", colorBlack);
	}

	// ========================================================
	// 6. ステージ選択中の表示
	// ========================================================
	if (state_ == SELECT_STATE::SELECT_STAGE)
	{
		std::string stageStr = "STAGE 1";
		if (gameInfo_.stage_ == STAGE_NUM::STAGE2) stageStr = "STAGE 2";
		if (gameInfo_.stage_ == STAGE_NUM::STAGE3) stageStr = "STAGE 3";

		// 中央の枠の下あたりにステージ名を表示
		DrawBox(centerX1 + 50, centerY2 - 50, centerX2 - 50, centerY2 - 10, colorBlack, TRUE);
		DrawBox(centerX1 + 50, centerY2 - 50, centerX2 - 50, centerY2 - 10, colorSelectEdge, FALSE);
		DrawString(centerX1 + 90, centerY2 - 35, stageStr.c_str(), GetColor(255, 255, 255));
	}

	// ========================================================
	// 7. 操作説明（操作ガイド）の描画
	// ========================================================
	int guideX = mainBoxX1 + 40;
	int guideY = mainBoxY2 + 15; // メイン枠のすぐ下

	// 基本操作テキストを組み立て
	std::string chooseStr = "【左右キー】選択";
	std::string decideStr = "【B / SPACE】決定";
	std::string cancelStr = "【A / UPキー】戻る";

	// 最初の状態（人数選択）の時は「戻る」を表示しない
	if (state_ == SELECT_STATE::SELECT_PLAYER_NUM)
	{
		std::string guideText = chooseStr + "   " + decideStr;
		DrawString(guideX, guideY, guideText.c_str(), colorBlack);
	}
	else
	{
		std::string guideText = chooseStr + "   " + decideStr + "   " + cancelStr;
		DrawString(guideX, guideY, guideText.c_str(), colorBlack);
	}
}

void GameSelectScene::SubRelease(void)
{
}

void GameSelectScene::SetGameStageNum(void)
{
}

void GameSelectScene::InitGameGroups(void)
{
	// テスト用のダミー割り当て (1人用、2人用にもテストデータを置いて確認できるようにします)
	onePlayerGames_ = {};
	twoPlayerGames_ = {};
	oneVsThreeGames_ = {};
	twoVsTwoGames_ = {};
	fourPlayerGames_ = {  GAME_KIND::FINDINGJ };

	currentGroup_ = &onePlayerGames_;
	cursorIndex_ = 0;
	state_ = SELECT_STATE::SELECT_PLAYER_NUM; // 初期状態

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

void GameSelectScene::UpdateGameGroups(void)
{
	bool isChangedPlayNum = false;

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::UP).down)
	{
		if (gameInfo_.playNum_ > PLAY_NUM::ONE_PLAYER)
		{
			gameInfo_.playNum_ = static_cast<PLAY_NUM>(static_cast<int>(gameInfo_.playNum_) - 1);
			isChangedPlayNum = true;
		}
	}

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::DOWN).down)
	{
		if (gameInfo_.playNum_ < PLAY_NUM::FOUR_PLAYER)
		{
			gameInfo_.playNum_ = static_cast<PLAY_NUM>(static_cast<int>(gameInfo_.playNum_) + 1);
			isChangedPlayNum = true;
		}
	}

	if (isChangedPlayNum)
	{
		cursorIndex_ = 0;
		
		switch (gameInfo_.playNum_)
		{
		case PLAY_NUM::ONE_PLAYER:   currentGroup_ = &onePlayerGames_;   break;
		case PLAY_NUM::TWO_PLAYER:   currentGroup_ = &twoPlayerGames_;   break;
		case PLAY_NUM::ONE_VS_THERR: currentGroup_ = &oneVsThreeGames_; break;
		case PLAY_NUM::TWO_VS_TWO: currentGroup_ = &twoVsTwoGames_; break;
		case PLAY_NUM::FOUR_PLAYER:  currentGroup_ = &fourPlayerGames_;  break;
		default:                     currentGroup_ = nullptr;            break;
		}

		if (currentGroup_ != nullptr && !currentGroup_->empty()) {
			gameInfo_.game_ = (*currentGroup_)[cursorIndex_];
		}
		else {
			gameInfo_.game_ = GAME_KIND::NONE;
		}
	}
}

void GameSelectScene::UpdateCursorIndex(void)
{
	if (currentGroup_ != nullptr && !currentGroup_->empty())
	{
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::LEFT).down)
		{
			if (cursorIndex_ > 0)
			{
				cursorIndex_--;
			}
		}
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::RIGHT).down)
		{
			if (cursorIndex_ < static_cast<int>(currentGroup_->size()) - 1)
			{
				cursorIndex_++;
			}
		}
		gameInfo_.game_ = (*currentGroup_)[cursorIndex_];
	}
	else
	{
		gameInfo_.game_ = GAME_KIND::NONE;
	}
}

void GameSelectScene::UpdateStageSelect(void)
{
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::LEFT).down)
	{
		if (gameInfo_.stage_ > STAGE_NUM::STAGE1)
		{
			gameInfo_.stage_ = static_cast<STAGE_NUM>(static_cast<int>(gameInfo_.stage_) - 1);
		}
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::RIGHT).down)
	{
		// STAGE_NUM::MAX の手前（STAGE3）まで進める
		if (gameInfo_.stage_ < static_cast<STAGE_NUM>(static_cast<int>(STAGE_NUM::MAX) - 1))
		{
			gameInfo_.stage_ = static_cast<STAGE_NUM>(static_cast<int>(gameInfo_.stage_) + 1);
		}
	}
}

void GameSelectScene::UpdatePlayerNumLeftRight(void)
{
	bool isChangedPlayNum = false;
	int currentNum = static_cast<int>(gameInfo_.playNum_);

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::LEFT).down)
	{
		if (currentNum > static_cast<int>(PLAY_NUM::ONE_PLAYER))
		{
			gameInfo_.playNum_ = static_cast<PLAY_NUM>(currentNum - 1);
			isChangedPlayNum = true;
		}
	}

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::RIGHT).down)
	{
		if (currentNum < static_cast<int>(PLAY_NUM::FOUR_PLAYER))
		{
			gameInfo_.playNum_ = static_cast<PLAY_NUM>(currentNum + 1);
			isChangedPlayNum = true;
		}
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
		default:                     currentGroup_ = nullptr;            break;
		}

		if (currentGroup_ != nullptr && !currentGroup_->empty()) {
			gameInfo_.game_ = (*currentGroup_)[cursorIndex_];
		}
		else {
			gameInfo_.game_ = GAME_KIND::NONE;
		}
	}
}