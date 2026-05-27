#pragma once
#include "SceneBase.h"
#include"../Scene/PauseScene.h"
class SceneManager;

class TitleScene :
    public SceneBase
{
public:
    TitleScene(void);
    ~TitleScene(void)override;

    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;

private:

    //ƒ^ƒCƒgƒ‹‰æ‘œ
    int imgTitle_;
    int imgPush_;

    bool isPause_ = false;

    std::shared_ptr<PauseScene> pauseScene_;

};

