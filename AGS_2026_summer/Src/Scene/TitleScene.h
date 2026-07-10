#pragma once
#include "SceneBase.h"
class TitleScene :
    public SceneBase
{
public:
    TitleScene(void);
    ~TitleScene(void)override;

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;
    SCENE_ID GetSceneID(void)const override { return SCENE_ID::TITLE; }
private:

	int imgTitle_;
    int logo_;
	int imgPush_;
    float angle_ = 0.0f; // —h‚ê—p‚ÌŠp“x—p•Ï”

};

