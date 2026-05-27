#pragma once
#include "SceneBase.h"
class PauseScene;
class TitleScene :
    public SceneBase
{
public:
    TitleScene(void);
    ~TitleScene(void)override;

    void Load(void)override;
    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;
    SCENE_ID GetSceneID(void)const override { return SCENE_ID::TITLE; }
private:

	int imgTitle_;
	int imgPush_;
	bool isPause_;


};

