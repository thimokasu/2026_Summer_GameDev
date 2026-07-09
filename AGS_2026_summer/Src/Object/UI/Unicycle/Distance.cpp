#include "distance.h"
#include <string>
#include "../../Common/Transform.h"

Distance::Distance(Vector2F pos)
    : UIBase(pos)
    , distance_(0.0f)
    , isUpdate_(false)
    , fontHandle_(-1)
    , scale_(0.2f)
    , textColor_(0)
    , edgeColor_(0)
    , bgColor_(0, 0, 0)
    , StartPos_(0)

{
	type_ = UITYPE::TEXT;
	textColor_ = GetColor(255, 255, 255);
	edgeColor_ = GetColor(0, 0, 0);
}

void Distance::SubLoad()
{
	bgHandle_ = LoadGraph("Data/Image/DistanceBG.png");
	//iconHandle_ = LoadGraph("Data/Image/TimerIcon.png");
	distanceHandle_ = LoadGraph("Data/Image/Distance.png");

	// ƒtƒHƒ“ƒg‚Ìì¬
	fontHandle_ = CreateFontToHandle("Arial", 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 2);

    StartPos_ = Transform_->pos.z;
}

void Distance::SubInit()
{
	uiName_ = UINAME::UNICYCLE_DISTANCE;
}

void Distance::SubUpdate()
{
	distance_ = (Transform_->pos.z - StartPos_)/20;
}

void Distance::SubDraw()
{
    // UIBase‚©‚ç‰æ–Êã‚Ìâ‘ÎÀ•W‚ğæ“¾
    Vector2F absPos = GetAbsolutePos();
    unsigned int white = GetColor(255, 255, 255);


    // ‰æ‚è”wŒi‚Ì•`‰æ
    SetDrawBright(bgColor_.x, bgColor_.y, bgColor_.z);
    DrawRotaGraph(absPos.x, absPos.y - IMAGE_HEIGHT_HALF* scale_, scale_, 0.0, bgHandle_, TRUE);
    SetDrawBright(255, 255, 255);

    // ”’‚¢”wŒi‚Ì•`‰æ
    //SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
    DrawRotaGraph(absPos.x, absPos.y - IMAGE_HEIGHT_HALF*scale_, scale_, 0.0, distanceHandle_, TRUE);
  //  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // ŒvƒAƒCƒRƒ“‚Ì•`‰æ
 //   DrawRotaGraph(absPos.x + 10.0f, absPos.y + size_.y / 1.8f, scale_ , 0.0, distanceHandle_, TRUE);

    // •¶š—ñ‚Ì¶¬‚Æ•`‰æ
    std::string timeString = std::to_string(static_cast<int>(distance_));

    //•¶š‚Ìİ’è
    double textScale = static_cast<double>(scale_ * 6.6f);
    int width = GetDrawStringWidthToHandle(timeString.c_str(), -1, fontHandle_);
    int height = GetFontSizeToHandle(fontHandle_);
    int textX = absPos.x - width;
    int textY = absPos.y - height* textScale-30;
    unsigned int fontColor = distance_ <= 6.0f ? GetColor(220, 0, 0) : GetColor(0, 0, 0);

    DrawRotaStringToHandle(
        textX, textY,
        textScale, textScale,
        0.0, 0.0, 0.0,
        fontColor, fontHandle_, white, FALSE,
        (timeString + "m").c_str());
}

void Distance::SubRelease() 
{
	DeleteGraph(bgHandle_);
	DeleteGraph(iconHandle_);
	DeleteGraph(distanceHandle_);
	DeleteFontToHandle(fontHandle_);
}
