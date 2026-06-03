#pragma once
#include "../UIBase.h" 
#include "../../../Common/IntVector3.h"
#include <functional>
// スペルを Callback に修正（任意ですがおすすめ）
using TimeUpCallback = std::function<void()>;

class Timer : public UIBase
{
public:
    // UIBaseのコンストラクタに合わせて引数を設定
    Timer(Vector2F pos, Vector2F size);
    virtual ~Timer() = default;

    float GetTime() const { return time_; }
    void Reset() { time_ = 10.0f; } // リセット時に初期時間に戻す
	void SetTimeUpCallback(TimeUpCallback callback) { timeUpCallback_ = std::move(callback); }
protected:
    // UIBaseの仮想関数をオーバーライド
    void SubLoad() override;
    void SubInit() override;
    void SubUpdate() override;
    void SubDraw() override;
    void SubRelease() override;

private:
    float time_;
    int bgHandle_;
    int iconHandle_;
    int clockHandle_;
    int fontHandle_; // 静的変数からメンバ変数へ昇格
    float scale_;
    IntVector3 bgColor_;
    TimeUpCallback timeUpCallback_;
};