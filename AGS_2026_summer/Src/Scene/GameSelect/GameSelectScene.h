#pragma once
#include "../SceneBase.h"
#include"GameKind.h"

class GameSelectScene :
    public SceneBase
{
public:
            GameSelectScene(void);
        ~GameSelectScene(void);
        void Load(void) override;
        void Init(void) override;
        void Update(void) override;
        void Draw(void) override;
        void Release(void) override;
		SCENE_ID GetSceneID(void)const override { return SCENE_ID::GAME_SELECT; }


private:
    GameInfo gameInfo_;
};
