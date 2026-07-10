#pragma once
#include "../UIBase.h"
#include<functional>

using ChangeSceneCallBack = std::function<void()>;

class MessageImageUI :
    public UIBase
{
    public:
    MessageImageUI(Vector2F pos);
    virtual ~MessageImageUI() = default;

    void SetChangeSceneCallBack(ChangeSceneCallBack callback) { changeSceneCallBack_ = std::move(callback); }
private:
    // UIBaseの仮想関数をオーバーライド
    void SubLoad() override;
    void SubInit() override;
    void SubUpdate() override;
    void SubDraw() override;
    void SubRelease() override;

    int imageHandle_ = -1;  
    int alpha_ = 255;
    ChangeSceneCallBack changeSceneCallBack_=nullptr;
};

