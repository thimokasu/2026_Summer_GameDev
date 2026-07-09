#include "CountTimer.h"
#include <string>
#include "../../../Manager/Game/SceneManager.h"

CountTimer::CountTimer(Vector2F pos)
    : UIBase(pos)
    , isUpdate_(true)
    , fontHandle_(-1)
    , scale_(0.2f)
    , textColor_(0)
    , edgeColor_(0)
    , bgColor_(0, 0, 0)
	, time_(3.0f)
	, angle_(0.0f)
	, countHandle_(-1)
	, yellowHandle_(-1)

{
    type_ = UITYPE::TEXT;
    textColor_ = GetColor(255, 255, 255);
    edgeColor_ = GetColor(0, 0, 0);
}

void CountTimer::SubLoad()
{
    fontHandle_ = CreateFontToHandle("Arial", 60, 6, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 3);
	countHandle_ = LoadGraph("Data/Image/Count.png");
	yellowHandle_ = LoadGraph("Data/Image/yellowCount.png");
}

void CountTimer::SubInit()
{
    uiName_ = UINAME::UNICYCLE_COUNT_TIMER;
}

void CountTimer::SubUpdate()
{

   time_ -= SceneManager::GetInstance().GetDeltaTime();
   
}

void CountTimer::SubDraw()
{

    if (time_ < -1.0f) { isUpdate_ = false; startCallBack_(); return; }


    // åªç›ÇÃïb(0Å`2)
    int second = static_cast<int>(time_);

    // ïbÇÃíÜÇÃåoâﬂ(0Å`1)
    float secTime = time_ - second;

    // åıÇÈÉ}ÉX
    int lightIndex = static_cast<int>(secTime * MARK_NUM);
   

    for (int i = 0; i < MARK_NUM; i++)
    {
        float angle = DX_PI_F * 2.0f * -i / MARK_NUM - DX_PI_F / 2.0f;

        float x = pos_.x + cosf(angle) * RADIUS;
        float y = pos_.y + sinf(angle) * RADIUS;

        bool light = (i == lightIndex);

        scale_ = light ? 0.4f : 0.3f;

        int handle = light ? yellowHandle_ : countHandle_;

        DrawRotaGraphF(
            x,
            y,
            scale_,
            angle,
            handle,
            TRUE);

    }

	// ï∂éöÇÃê›íË
    std::string text;
	text = time_ > 0 ? std::to_string(static_cast<int>(ceilf(time_))) : "GO!";

	// ï∂éöÇÃï`âÊà íuÇ∆ÉXÉPÅ[ÉãÇåvéZ
    double textScale = time_ > 0 ? static_cast<double>(scale_ * 6.0f) : static_cast<double>(scale_ * 4.0f);
    unsigned int fontColor =  GetColor(0, 255, 255);
    unsigned int white = GetColor(255, 255, 255);
    int width = GetDrawStringWidthToHandle(text.c_str(), -1, fontHandle_);
    int height = GetFontSizeToHandle(fontHandle_);
    int textX = pos_.x - width/2* textScale;
    int textY = pos_.y - height/2* textScale;

	// ï∂éöóÒÇÃï`âÊ
    DrawRotaStringToHandle(
        textX, textY,
        textScale, textScale,
        0.0, 0.0, 0.0,
        fontColor, fontHandle_, white, FALSE,
        text.c_str());
    

}

void CountTimer::SubRelease()
{

    DeleteFontToHandle(fontHandle_);
    DeleteGraph(countHandle_);
    DeleteGraph(yellowHandle_);

}
