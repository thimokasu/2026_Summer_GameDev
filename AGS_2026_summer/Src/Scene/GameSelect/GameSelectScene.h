#pragma once
#include "../SceneBase.h"
#include<vector>
#include<unordered_map>

#include"GameInfo.h"

class GameSelectScene :
    public SceneBase
{
public:
    static const std::string PATH_GAMESELECTSCENE;


    // アニメーションのフェーズを分けるための定数
    const int SCALE_UP_TIME = 5;   // 拡大する時間（5フレーム）
    const int SCALE_DOWN_TIME = 20; // 縮小する時間（15フレーム）

    enum class SELECT_STATE
    {
        SELECTING,
        TRANSITIONING,
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

    void LoadImages(void);

    void InitGameGroups(void);
    void InitUI(void) override;
    void InitSE(void) override;

    using Update_t = void(GameSelectScene::*)(void);
    using Draw_t = void(GameSelectScene::*)(void);

    Update_t update_;
    Draw_t draw_;

    void UpdatePlayNumSelect(void);
    void UpdateGameSelect(void);
    void UpdateStageSelect(void);

    void DrawPlayNumSelect(void);
    void DrawGameSelect(void);
    void DrawStageSelect(void);
#pragma endregion

#pragma region 変数
    std::vector<GAME_KIND>onePlayerGames_;
    std::vector<GAME_KIND>twoPlayerGames_;
    std::vector<GAME_KIND>oneVsThreeGames_;
    std::vector<GAME_KIND>twoVsTwoGames_;
	std::vector<GAME_KIND>fourPlayerGames_;
    std::vector<GAME_KIND>oneToFourPlayGames_;
    const std::vector<GAME_KIND>* currentGroup_ = nullptr;
    std::unordered_map<GAME_KIND, int>gameImageHandles_;
    std::unordered_map<GAME_KIND, int>gameTitleHandles_;
    std::unordered_map<GAME_KIND, int>gameIntroductionHandles_;
	int cursorIndex_ = 0;
    GameInfo gameInfo_;
    SELECT_STATE state_ = SELECT_STATE::SELECTING;
    int transitionTimer_ = 0;
    int backImage_ = -1;
    int fontHandle_ = -1; // クラスのメンバ変数として追加
#pragma endregion
};
