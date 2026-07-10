#include "MessageImageUI.h"

MessageImageUI::MessageImageUI(Vector2F pos)
    : UIBase(pos)
	
{
}

void MessageImageUI::SubLoad()
{
	handleId_ = LoadGraph("Data/Image/Miracle.png");
	isActive_ = false;
}

void MessageImageUI::SubInit()
{
}

void MessageImageUI::SubUpdate()
{
}

void MessageImageUI::SubDraw()
{
    if (isActive_)
    {
        alpha_ -= 1;
        if (alpha_ < 0)
        {
            alpha_ = 0;
            isActive_ = false;
        }

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
        DrawRotaGraphF(pos_.x, pos_.y, 0.8f, 0.0f, handleId_, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void MessageImageUI::SubRelease()
{
}
