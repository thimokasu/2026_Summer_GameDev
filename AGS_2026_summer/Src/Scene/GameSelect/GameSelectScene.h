#pragma once
#include "../SceneBase.h"
#include<vector>
#include<unordered_map>

#include"GameKind.h"

class GameSelectScene :
    public SceneBase
{
public:
            GameSelectScene(void);
        ~GameSelectScene(void);
        void SubLoad(void) override;
        void SubInit(void) override;
        void SubUpdate(void) override;
        void SubDraw(void) override;
        void SubRelease(void) override;
		SCENE_ID GetSceneID(void)const override { return SCENE_ID::GAME_SELECT; }
private:
#pragma region  ä÷êî
    void SetGameStageNum(void);
	
    void InitGameGroups(void);
	void InitUI(void) override;
	void InitSE(void) override;

	void UpdateGameGroups(void);
	void UpdateCursorIndex(void);
#pragma endregion

#pragma region ïœêî
    std::vector<GAME_KIND>onePlayerGames_;
	std::vector<GAME_KIND>twoPlayerGames_;
	std::vector<GAME_KIND>threePlayerGames_;
	std::vector<GAME_KIND>fourPlayerGames_;
    const std::vector<GAME_KIND>* currentGroup_ = nullptr;
	int cursorIndex_ = 0;
    GameInfo gameInfo_;
#pragma endregion
};
