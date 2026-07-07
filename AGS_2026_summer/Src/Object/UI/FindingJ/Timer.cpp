#include "Timer.h"
#include <DxLib.h>
#include <cmath>
#include"../../../Manager/Game/SceneManager.h"
#include"../../../Manager/Game/SE.h"

Timer::Timer(Vector2F pos, Vector2F size)
	:UIBase(pos, size)
    , time_(30.0f)
    , bgHandle_(-1)
    , iconHandle_(-1)
    , clockHandle_(-1)
    , fontHandle_(-1)
    , scale_(0.15f)
    , bgColor_(0, 0, 0)
{
	type_ = UITYPE::IMAGE;
}

void Timer::SubLoad()
{
    bgHandle_ = LoadGraph("Data/Image/TimerBG.png");
    iconHandle_ = LoadGraph("Data/Image/TimerIcon.png");
    clockHandle_ = LoadGraph("Data/Image/Clock.png");

    fontHandle_ = CreateFontToHandle("Arial", 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 2);
    SE::GetInstance().Load(SOUND_TYPE::ALERT, "Data/BGM/Alert.mp3");

}

void Timer::SubInit()
{
    uiName_ = UINAME::FINDINGJ_TIMER;
}

void Timer::SubUpdate()
{
    if (!isUpdate_)return;
    // time_ が 0 になったら減算をストップ（マイナスにいき続けないように）
    if (time_ > 0.0f)
    {
        time_ -= SceneManager::GetInstance().GetDeltaTime();
    }

    if (time_ <= 0.0f)
    {
        time_ = 0.0f;
        if (timeUpCallback_)
        {
            timeUpCallback_();
            timeUpCallback_ = nullptr; // 1回だけ呼ぶためにクリア（運用に合わせて）
        }
    }
}

void Timer::SubDraw()
{
    // UIBaseから画面上の絶対座標を取得！
    Vector2F absPos = GetAbsolutePos();
    unsigned int white = GetColor(255, 255, 255);

    // 基本の拡大率
    scale_ = 0.15f;

    if (time_ <= 6.0f && time_ > 0.0f)
    {
        bgColor_ = { 220, 0, 0 };

        float fract = time_ - std::floor(time_);
        if (fract > 0.7f)
        {
            float wave = std::sin((fract - 0.7f) / 0.3f * DX_PI_F);
            scale_ = 0.15f + wave * 0.03f;
            SE::GetInstance().Play(SOUND_TYPE::ALERT, false);
        }
    }
    else
    {
        bgColor_ = { 0, 0, 0 };
        if (SE::GetInstance().IsEnd(SOUND_TYPE::ALERT))
        {
            SE::GetInstance().Play(SOUND_TYPE::ALERT, false);
        }
    }

    // 縁取り背景の描画
    SetDrawBright(bgColor_.x, bgColor_.y, bgColor_.z);
    DrawRotaGraph(absPos.x + size_.x / 2.5f, absPos.y + size_.y / 1.8f, scale_, 0.0, bgHandle_, TRUE);
    SetDrawBright(255, 255, 255);

    // 白い背景の描画
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
    DrawRotaGraph(absPos.x + size_.x / 2.5f, absPos.y + size_.y / 1.8f, scale_, 0.0, iconHandle_, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // 時計アイコンの描画
    DrawRotaGraph(absPos.x + 10.0f, absPos.y + size_.y / 1.8f, scale_ - 0.09f, 0.0, clockHandle_, TRUE);

    // 文字列の生成と描画
    char timeString[32];
    sprintf_s(timeString, "%d", static_cast<int>(time_));

    int textX = absPos.x + 110;
    int textY = absPos.y + 10;
    double textScale = static_cast<double>(scale_ * 6.6f);
    unsigned int fontColor = time_ <= 6.0f ? GetColor(220, 0, 0) : GetColor(0, 0, 0);

    DrawRotaStringToHandle(
        textX, textY,
        textScale, textScale,
        0.0, 0.0, 0.0,
        fontColor, fontHandle_, white, FALSE,
        timeString
    );
}

void Timer::SubRelease()
{
    DeleteGraph(bgHandle_);
    DeleteGraph(iconHandle_);
    DeleteGraph(clockHandle_);
    DeleteFontToHandle(fontHandle_);
}
