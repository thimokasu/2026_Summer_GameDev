#pragma once
#include "../SceneBase.h"
#include<vector>
#include<unordered_map>

#include"GameInfo.h"

class GameSelectScene :
    public SceneBase
{
public:

    enum class SELECT_STATE {
        SELECT_PLAYER_NUM, // 人数選択
        SELECT_GAME,       // ゲーム選択
        SELECT_STAGE,      // ステージ選択
    };
    GameSelectScene(void);
    ~GameSelectScene(void);
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
    SCENE_ID GetSceneID(void)const override { return SCENE_ID::GAME_SELECT; }
private:
#pragma region  関数
    void SetGameStageNum(void);

    void InitGameGroups(void);
    void InitUI(void) override;
    void InitSE(void) override;

    void UpdateGameGroups(void);
    void UpdateCursorIndex(void);
    void UpdateStageSelect(void);
    void UpdatePlayerNumLeftRight(void);
#pragma endregion

#pragma region 変数
    std::vector<GAME_KIND>onePlayerGames_;
    std::vector<GAME_KIND>twoPlayerGames_;
    std::vector<GAME_KIND>oneVsThreeGames_;
    std::vector<GAME_KIND>twoVsTwoGames_;
	std::vector<GAME_KIND>fourPlayerGames_;
    const std::vector<GAME_KIND>* currentGroup_ = nullptr;
	int cursorIndex_ = 0;
    GameInfo gameInfo_;
    SELECT_STATE state_ = SELECT_STATE::SELECT_PLAYER_NUM;
#pragma endregion
};
