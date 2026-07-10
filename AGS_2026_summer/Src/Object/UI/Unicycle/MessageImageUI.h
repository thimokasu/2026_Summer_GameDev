#pragma once
#include "../UIBase.h"

class MessageImageUI :
    public UIBase
{
    public:
    MessageImageUI(Vector2F pos);
    virtual ~MessageImageUI() = default;

private:
    // UIBaseの仮想関数をオーバーライド
    void SubLoad() override;
    void SubInit() override;
    void SubUpdate() override;
    void SubDraw() override;
    void SubRelease() override;

    int imageHandle_ = -1;  
    int alpha_ = 255;

};

