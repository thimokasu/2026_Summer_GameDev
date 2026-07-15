#include "GameMessageUI.h"
#include "../../../Manager/Game/SceneManager.h"
#include "../../../Application.h"

GameMessageUI::GameMessageUI(Vector2F pos, Vector2F size)
    :UIBase(pos, size)
{
    fontHandle_ = -1;
    currentState_ = MASSAGE_STATE::EXPLAIN;
    animPhase_ = ANIM_PHASE::FADE_IN;
    animTime_ = 0.0f;
    scaleX_ = 0.0f;
    scaleY_ = 0.0f;
    type_ = UITYPE::TEXT;
    textColor_ = GetColor(255, 255, 255);
    edgeColor_ = GetColor(0, 0, 0);
}

void GameMessageUI::SubLoad(void)
{
    if (fontHandle_ == -1)
    {
        fontHandle_ = CreateFontToHandle("Arial", FontSize, 6, DX_FONTTYPE_ANTIALIASING_EDGE, -1, EdgeSize);
    }
}

void GameMessageUI::SubInit(void)
{
    uiName_ = UINAME::MASSAGE;
    currentState_ = MASSAGE_STATE::EXPLAIN;
    animTime_ = 0.0f;
    scaleX_ = 0.0f;
    scaleY_ = 0.0f;
    animPhase_ = ANIM_PHASE::FADE_IN;
}

void GameMessageUI::SubUpdate(void)
{
    if (currentState_ != MASSAGE_STATE::NONE)
    {
        animTime_ += SceneManager::GetInstance().GetDeltaTime();
        TextAnim();
    }
    if (currentState_ == MASSAGE_STATE::START)
    {
        if (animPhase_ == ANIM_PHASE::FADE_OUT)
        {        
            //startCallBack_();
            
        }
    }
    if (currentState_ == MASSAGE_STATE::FINISH)
    {
        if (animPhase_ == ANIM_PHASE::FADE_OUT)
        {
            SceneManager::GetInstance().PushScene(SCENE_ID::PAUSE);
            SetMassageState(MASSAGE_STATE::NONE);
            animPhase_ = ANIM_PHASE::NONE;
        }
    }
}


void GameMessageUI::SubDraw(void)
{
    if (currentState_ == MASSAGE_STATE::NONE) return;
    std::string text = "";
    if (messageMap_.count(currentState_)) {
        text = messageMap_[currentState_];
    }
    if (text.empty()) return;
    const char* targetStr = text.c_str();

    int stringWidth = 0;
    int stringHeight = 0;
    GetDrawStringSizeToHandle(&stringWidth, &stringHeight, nullptr, targetStr, (int)text.length(), fontHandle_);
    float cx = stringWidth / 2.0f;
    float cy = stringHeight / 2.0f;

    // UIBaseから絶対座標を取得
    Vector2F absPos = GetAbsolutePos();

    int width = GetDrawStringWidthToHandle(targetStr, -1, fontHandle_);
    int height = GetFontSizeToHandle(fontHandle_);

    // UIBaseのsize_の中心を描画の基準点（画面中央など）にする
    int drawX = static_cast<int>(absPos.x);
    int drawY = static_cast<int>(absPos.y);

    // ゲーム説明の時だけ文字の後ろに帯を出す
    if (currentState_ == MASSAGE_STATE::EXPLAIN)
    {
        int paddingY = 20;
        int barTop = drawY - (int)cy - paddingY;
        int barBottom = drawY + (int)cy + paddingY;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
        // 帯は画面サイズに合わせる
        DrawBox(0, barTop, Application::SCREEN_SIZE_X, barBottom, GetColor(0, 0, 0), TRUE);
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

void GameMessageUI::SubRelease(void)
{
    if (fontHandle_ != -1)
    {
        DeleteFontToHandle(fontHandle_);
        fontHandle_ = -1;
    }
}

void GameMessageUI::SetMassageState(MASSAGE_STATE state)
{
    animTime_ = 0.0f;
    scaleX_ = 0.0f;
    scaleY_ = 0.0f;
    animPhase_ = ANIM_PHASE::FADE_IN;
    currentState_ = state;
    switch (state)
    {
    case GameMessageUI::MASSAGE_STATE::NONE:
        break;
    case GameMessageUI::MASSAGE_STATE::EXPLAIN:
        textColor_ = GetColor(255, 255, 255);
        edgeColor_ = GetColor(0, 0, 0);
        break;
    case GameMessageUI::MASSAGE_STATE::START:
        textColor_ = GetColor(0, 200, 255);
        edgeColor_ = GetColor(255, 255, 255);
        break;
    case GameMessageUI::MASSAGE_STATE::FINISH:
        textColor_ = GetColor(255, 215, 0);
        edgeColor_ = GetColor(255, 255, 255);
        break;
    }

}

void GameMessageUI::TextAnim(void)
{
    static constexpr float ChangeSpeedIN = 0.02f;
    static constexpr float ChangeSpeedOut = 0.04f;
    static constexpr float StayTimeSeconds = 2.0f; // DeltaTime(秒)に合わせるため型と基準を変更

    switch (animPhase_)
    {
    case GameMessageUI::ANIM_PHASE::FADE_IN:
        scaleX_ += ChangeSpeedIN;
        scaleY_ += ChangeSpeedIN;

        if (scaleX_ >= 1.0f)
        {
            scaleX_ = 1.0f;
            scaleY_ = 1.0f;
            animTime_ = 0.0f;
            animPhase_ = ANIM_PHASE::STAY;
        }
        break;
    case GameMessageUI::ANIM_PHASE::STAY:
        if (animTime_ >= StayTimeSeconds)
        {
            animPhase_ = ANIM_PHASE::FADE_OUT;
        }
        break;
    case GameMessageUI::ANIM_PHASE::FADE_OUT:
        scaleX_ -= ChangeSpeedOut;
        scaleY_ -= ChangeSpeedOut;

        if (scaleX_ <= 0.0f)
        {
            scaleX_ = 0.0f;
            scaleY_ = 0.0f;
            if (currentState_ == MASSAGE_STATE::EXPLAIN)
            {
                SetMassageState(MASSAGE_STATE::START);
                return;
            }
            SetMassageState(MASSAGE_STATE::NONE);
        }
        break;
    }
}

void GameMessageUI::SetMassageText(MASSAGE_STATE state, const std::string& text)
{
    messageMap_[state] = text;
}

