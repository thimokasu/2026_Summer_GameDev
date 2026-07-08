#pragma once
#include "../UIBase.h"
#include "../../../Common/IntVector3.h"


class Distance : public UIBase
{
public:
    // UIBaseのコンストラクタに合わせて引数を設定
    Distance(Vector2F pos, Vector2F size);
    virtual ~Distance() = default;
    void SetUpdate(bool flag) { isUpdate_ = flag; }
protected:
    // UIBaseの仮想関数をオーバーライド
    void SubLoad() override;
    void SubInit() override;
    void SubUpdate() override;
    void SubDraw() override;
    void SubRelease() override;

private:
    float time_;
    bool isUpdate_ = false;
    int fontHandle_; // 静的変数からメンバ変数へ昇格
    float scale_;
    
};
