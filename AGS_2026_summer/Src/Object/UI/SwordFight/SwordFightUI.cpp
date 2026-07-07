#include "SwordFightUI.h"
#include "../../../Manager/Game/SceneManager.h"


SwordFightUI::SwordFightUI(Vector2F pos, Vector2F size)
    : UIBase(pos, size)
    , fontHandle_(-1)
    , currentState_(MessageState::Idle)
    , animPhase_(AnimPhase::FadeIn)
    , animTime_(0.0f)
    , scaleX_(0.0f)
    , scaleY_(0.0f)
{
    type_ = UITYPE::TEXT;
    textColor_ = GetColor(255, 255, 255);
    edgeColor_ = GetColor(0, 0, 0);
}

void SwordFightUI::SubLoad()
{
    if (fontHandle_ == -1)
    {
        fontHandle_ = CreateFontToHandle("Arial", FontSize, 6, DX_FONTTYPE_ANTIALIASING_EDGE, -1, EdgeSize);
    }
}

void SwordFightUI::SubInit()
{
    uiName_ = UINAME::SWORD_FIGHT_MASSAGE;
    animTime_ = 0.0f;
    scaleX_ = 0.0f;
    scaleY_ = 0.0f;
    animPhase_ = AnimPhase::FadeIn;
}


void SwordFightUI::SetState(MessageState state)
{
    currentState_ = state;
    animTime_ = 0.0f;
    scaleX_ = 0.0f;
    scaleY_ = 0.0f;
    animPhase_ = AnimPhase::FadeIn;

    switch (currentState_)
    {
    case MessageState::Start:
        textColor_ = GetColor(0, 200, 255);
        edgeColor_ = GetColor(255, 255, 255);
        break;
    case MessageState::Finish:
        textColor_ = GetColor(255, 215, 0);
        edgeColor_ = GetColor(255, 255, 255);
        break;
    case MessageState::Idle:
        textColor_ = GetColor(255, 255, 255);
        edgeColor_ = GetColor(0, 0, 0);
        break;
    case MessageState::Draw:
        textColor_ = GetColor(255, 255, 255);
		edgeColor_ = GetColor(255, 0, 0);
    default:
        break;
    }
}

void SwordFightUI::SubUpdate()
{
    if (currentState_ != MessageState::None)
    {
        animTime_ += SceneManager::GetInstance().GetDeltaTime();
        TextAnim();
    }
}
void SwordFightUI::TextAnim(void)
{
    static constexpr float ChangeSpeedIN = 0.02f;
    static constexpr float ChangeSpeedOut = 0.04f;
    static constexpr float StayTimeSeconds = 2.0f; // DeltaTime(秒)に合わせるため型と基準を変更

    switch (animPhase_)
    {
    case AnimPhase::FadeIn:
        scaleX_ += ChangeSpeedIN;
        scaleY_ += ChangeSpeedIN;

        if (scaleX_ >= 1.0f)
        {
            scaleX_ = 1.0f;
            scaleY_ = 1.0f;
            animTime_ = 0.0f;
            animPhase_ = AnimPhase::Stay;
        }
        break;

    case AnimPhase::Stay:
        if (animTime_ >= StayTimeSeconds)
        {
            animPhase_ = AnimPhase::FadeOut;
        }
        break;

    case AnimPhase::FadeOut:
        scaleX_ -= ChangeSpeedOut;
        scaleY_ -= ChangeSpeedOut;

        if (scaleX_ <= 0.0f)
        {
            scaleX_ = 0.0f;
            scaleY_ = 0.0f;

            if (currentState_ == MessageState::Idle)
            {
                SetState(MessageState::Start);
                return;
            }
            SetState(MessageState::None);
        }
        break;
    }
}


void SwordFightUI::SubDraw()
{
    if (currentState_ == MessageState::None) return;

    const char* targetStr = nullptr;
    switch (currentState_)
    {
    case MessageState::Start:   targetStr = StrStart;   break;
    case MessageState::Finish:  targetStr = StrFinish;  break;
    case MessageState::Idle: targetStr = StrIdle; break;
    case MessageState::Draw: targetStr = StrDraw; break;
    default: return;
    }

    if (targetStr == nullptr) return;

    int stringWidth = 0;
    int stringHeight = 0;
    GetDrawStringSizeToHandle(&stringWidth, &stringHeight, nullptr, targetStr, (int)strlen(targetStr), fontHandle_);

    float cx = stringWidth / 2.0f;
    float cy = stringHeight / 2.0f;

    // UIBaseから絶対座標を取得
    Vector2F absPos = GetAbsolutePos();

    // UIBaseのsize_の中心を描画の基準点（画面中央など）にする
    int drawX = static_cast<int>(absPos.x + size_.x / 2.0f);
    int drawY = static_cast<int>(absPos.y + size_.y / 2.0f);

    // ゲーム説明の時だけ文字の後ろに帯を出す
    if (currentState_ == MessageState::Idle)
    {
        int paddingY = 20;
        int barTop = drawY - (int)cy - paddingY;
        int barBottom = drawY + (int)cy + paddingY;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
        // 親から与えられた横幅（size_.x）いっぱいに帯を描画
        DrawBox(static_cast<int>(absPos.x), barTop, static_cast<int>(absPos.x + size_.x), barBottom, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    DrawRotaStringToHandle(
        drawX, drawY,
        scaleX_, scaleY_,
        cx, cy,
        0.0,
        textColor_,
        fontHandle_,
        edgeColor_,
        FALSE,
        targetStr
    );
}

void SwordFightUI::SubRelease()
{
    if (fontHandle_ != -1)
    {
        DeleteFontToHandle(fontHandle_);
        fontHandle_ = -1;
    }
}
