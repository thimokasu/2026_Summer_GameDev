#pragma once
#include "../UIBase.h" 
#include "../../../Common/IntVector3.h"
#include <functional>

using TimeUpCallBack = std::function<void()>;

class Timer : public UIBase
{

public:

    //画像サイズ

public:
    // UIBaseのコンストラクタに合わせて引数を設定
    Timer(Vector2F pos, Vector2F size);
    virtual ~Timer() = default;
    void SetTimeUpCallBack(TimeUpCallBack callBack) { timeUpCallback_ = std::move(callBack); }
    void SetUpdate(bool flag) { isUpdate_ = flag; }
    void SetTime(int time) { time_ = time; }
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
    int bgHandle_;
    int iconHandle_;
    int clockHandle_;
    int fontHandle_; // 静的変数からメンバ変数へ昇格
    float scale_;
    IntVector3 bgColor_;
    TimeUpCallBack timeUpCallback_;
};