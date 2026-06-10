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

	bool isAlreadyLeftEndGame = (cursorIndex_ == 0);
	bool isAlreadyFirstStage = (gameInfo_.stage_ == STAGE_NUM::STAGE1);

	// 現在の状態に応じて、呼ぶ更新関数を切り替える
	switch (state_)
	{
	case SELECT_STATE::SELECT_PLAYER_NUM:
		UpdateGameGroups(); // 上下で人数を選ぶ処理

		// 【スペースで決定】人数を確定してゲーム選択へ
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
		{
			if (!currentGroup_->empty())
			{
				state_ = SELECT_STATE::SELECT_GAME;
				cursorIndex_ = 0; // ゲーム選択のカーソルをリセット
				gameInfo_.game_ = (*currentGroup_)[cursorIndex_];
			}
		}
		break;

	case SELECT_STATE::SELECT_GAME:
		// 【修正ポイント】
		// 先に「すでに左端（0）にいるか」を記録しておきます
		isAlreadyLeftEndGame = (cursorIndex_ == 0);

		UpdateCursorIndex(); // 左右でゲームを選ぶ処理（ここで左を押すと0に向かって進む）

		// 左右の移動処理が終わった「後」に判定
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::LEFT).down)
		{
			// 移動する前からすでに左端にいた、かつ、もう一回左が押されたなら戻る
			if (isAlreadyLeftEndGame)
			{
				state_ = SELECT_STATE::SELECT_PLAYER_NUM;
			}
		}

		// 【スペースで決定】ゲームを確定してステージ選択へ
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
		{
			state_ = SELECT_STATE::SELECT_STAGE;
			gameInfo_.stage_ = STAGE_NUM::STAGE1;
		}
		break;

	case SELECT_STATE::SELECT_STAGE:
		// 【修正ポイント】
		// 先に「すでに最初のステージ（STAGE1）にいるか」を記録
		isAlreadyFirstStage = (gameInfo_.stage_ == STAGE_NUM::STAGE1);

		UpdateStageSelect(); // 左右でステージを変更する処理

		// 左右の移動処理が終わった「後」に判定
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::LEFT).down)
		{
			// 移動する前からすでにSTAGE1にいた、かつ、もう一回左が押されたなら戻る
			if (isAlreadyFirstStage)
			{
				state_ = SELECT_STATE::SELECT_GAME;
			}
		}

		// 【スペースで決定】ステージを確定してGameSceneへ遷移！
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
		{
			SceneManager::GetInstance().ChangeScene<GameScene>(gameInfo_);
		}
		break;
	}
}
void GameSelectScene::SubDraw(void)
{
	// ========================================================
	// 1. プレイ人数の文字列変換
	// ========================================================
	std::string playNumStr = "";
	switch (gameInfo_.playNum_)
	{
	case PLAY_NUM::ONE_PLAYER:   playNumStr = "1 PLAYER";   break;
	case PLAY_NUM::TWO_PLAYER:   playNumStr = "2 PLAYERS";  break;
	case PLAY_NUM::THREE_PLAYER: playNumStr = "3 PLAYERS";  break;
	case PLAY_NUM::FOUR_PLAYER:  playNumStr = "4 PLAYERS";  break;
	}

	// ========================================================
	// 2. 現在のステージの文字列変換
	// ========================================================
	std::string stageStr = "";
	switch (gameInfo_.stage_)
	{
	case STAGE_NUM::STAGE1: stageStr = "STAGE 1"; break;
	case STAGE_NUM::STAGE2: stageStr = "STAGE 2"; break;
	case STAGE_NUM::STAGE3: stageStr = "STAGE 3"; break;
	default:                stageStr = "UNKNOWN"; break;
	}

	int totalGamesInGroup = currentGroup_ ? static_cast<int>(currentGroup_->size()) : 0;

	// ========================================================
	// 3. 画面へのデバッグ描画（状態に合わせて色が変わる）
	// ========================================================
	unsigned int textColor = 0xFFFFFF;  // 白色 (通常)
	unsigned int activeColor = 0x00FF00;  // 緑色 (現在操作中)
	unsigned int alertColor = 0xFF0000;  // 赤色 (エラー・空)

	unsigned int pNumColor = (state_ == SELECT_STATE::SELECT_PLAYER_NUM) ? activeColor : textColor;
	unsigned int gameColor = (state_ == SELECT_STATE::SELECT_GAME) ? activeColor : textColor;
	unsigned int stageColor = (state_ == SELECT_STATE::SELECT_STAGE) ? activeColor : textColor;

	DrawString(50, 50, "--- GAME SELECT DEBUG ---", textColor);

	// 人数情報
	std::string infoPlayer = "1. [Player Num] : " + playNumStr;
	DrawString(50, 100, infoPlayer.c_str(), pNumColor);

	// ゲーム情報
	std::string infoGame = "2. [Selected Game] : " + gameInfo_.GetGameName();
	unsigned int actualGameColor = (gameInfo_.game_ == GAME_KIND::NONE) ? alertColor : gameColor;
	DrawString(50, 140, infoGame.c_str(), actualGameColor);

	// ステージ情報
	std::string infoStage = "3. [Selected Stage] : " + stageStr;
	// ゲームが確定していない、または人数選択中はステージ情報を少し暗く見せる処理をしても良いです
	DrawString(50, 180, infoStage.c_str(), stageColor);

	// 4. グループ内リストの簡易表示
	DrawString(50, 240, "=== Current Group List ===", textColor);
	if (totalGamesInGroup == 0)
	{
		DrawString(70, 270, "( Empty )", 0x888888);
	}
	else
	{
		for (int i = 0; i < totalGamesInGroup; ++i)
		{
			// ゲーム選択中のみカーソル矢印を表示
			std::string prefix = (i == cursorIndex_ && state_ == SELECT_STATE::SELECT_GAME) ? "-> " : "   ";

			GameInfo tempInfo;
			tempInfo.game_ = (*currentGroup_)[i];
			std::string listItem = prefix + "Slot " + std::to_string(i) + " : " + tempInfo.GetGameName();

			unsigned int color = (i == cursorIndex_ && state_ == SELECT_STATE::SELECT_GAME) ? activeColor : textColor;
			DrawString(70, 270 + (i * 25), listItem.c_str(), color);
		}
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
	onePlayerGames_ = { GAME_KIND::TEST_ONE };
	twoPlayerGames_ = { GAME_KIND::TEST_TWO };
	threePlayerGames_ = {};
	fourPlayerGames_ = { GAME_KIND::TEST_FOUR, GAME_KIND::FINDINGJ };

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
		case PLAY_NUM::THREE_PLAYER: currentGroup_ = &threePlayerGames_; break;
		case PLAY_NUM::FOUR_PLAYER:  currentGroup_ = &fourPlayerGames_;  break;
		}

		// グループが変わったら、選択中ゲームの初期表示も更新
		if (!currentGroup_->empty()) {
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

// ========================================================
// 【新設】左右キーでのステージ選択処理
// ========================================================
void GameSelectScene::UpdateStageSelect(void)
{
	// 本来はゲームごとに「最大ステージ数」を変えますが、
	// 今回はSTAGE_NUM::MAX（3つ）を上限として制御します。

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

void GameSelectScene::ChangeGame(GameInfo info)
{
	switch (info.playNum_)
	{
	case PLAY_NUM::ONE_PLAYER:
		CreateGameOne(info);
		break;
	case PLAY_NUM::TWO_PLAYER:
		CreateGameTwo(info);
		break;
	case PLAY_NUM::THREE_PLAYER:
		CreateGameTherr(info);
		break;
	case PLAY_NUM::FOUR_PLAYER:
		CreateGameFour(info);
		break;
	default:
		break;
	}
}

void GameSelectScene::CreateGameOne(GameInfo info)
{
}

void GameSelectScene::CreateGameTwo(GameInfo info)
{
}

void GameSelectScene::CreateGameTherr(GameInfo info)
{
}

void GameSelectScene::CreateGameFour(GameInfo info)
{

}
