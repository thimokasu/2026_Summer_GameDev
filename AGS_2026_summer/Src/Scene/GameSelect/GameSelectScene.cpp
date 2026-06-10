#include "GameSelectScene.h"
#include"../../Manager/Generic/KeyManager.h"

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
	UpdateGameGroups();
	UpdateCursorIndex();
}

void GameSelectScene::SubDraw(void)
{
}

void GameSelectScene::SubRelease(void)
{
}

void GameSelectScene::SetGameStageNum(void)
{

}

void GameSelectScene::InitGameGroups(void)
{
	onePlayerGames_ = {};
	twoPlayerGames_ = {};
	threePlayerGames_ = {};
	fourPlayerGames_ = {GAME_KIND::FINDINGJ};
	currentGroup_ = &onePlayerGames_;
	cursorIndex_ = 0;
	gameInfo_.game_ = (*currentGroup_)[cursorIndex_];
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
		cursorIndex_ = 0;	//グループのゲームの先頭に合わせる
		switch (gameInfo_.playNum_)
		{
		case PLAY_NUM::ONE_PLAYER:   currentGroup_ = &onePlayerGames_;   break;
		case PLAY_NUM::TWO_PLAYER:   currentGroup_ = &twoPlayerGames_;   break;
		case PLAY_NUM::THREE_PLAYER: currentGroup_ = &threePlayerGames_; break;
		case PLAY_NUM::FOUR_PLAYER:  currentGroup_ = &fourPlayerGames_;  break;
		default:
			break;
		}
	}
}

void GameSelectScene::UpdateCursorIndex(void)
{
	if(currentGroup_!=nullptr&&!currentGroup_->empty())
	{
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::LEFT).down)
		{
			if(cursorIndex_>0)
			{
				cursorIndex_--;
			}
		}
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::RIGHT).down)
			{
			if(cursorIndex_<currentGroup_->size()-1)
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
