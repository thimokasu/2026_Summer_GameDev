#pragma once
#include "../UIBase.h"

class SwordFightUI : public UIBase
{
public:
    static constexpr int FontSize = 100;
    static constexpr int EdgeSize = 4;

	static constexpr const char* StrIdle = "構えっ！";
    static constexpr const char* StrStart = "始めっ！";
    static constexpr const char* StrDraw = "やめっ！";
    static constexpr const char* StrFinish = "勝負あり！";
    static constexpr const char* StrNone = "";

    enum class MessageState
    {
        None,
        Idle,
        Start,
		Draw,
        Finish,
    };

public:
    // UIBaseのコンストラクタに合わせる
    SwordFightUI(Vector2F pos, Vector2F size);
    virtual ~SwordFightUI() = default;

    void SetState(MessageState state);
    MessageState GetStateUI(void) const { return currentState_; }

protected:
    // UIBaseの仮想関数をオーバーライド
    void SubLoad() override;
    void SubInit() override;
    void SubUpdate() override;
    void SubDraw() override;
    void SubRelease() override;

private:
    void TextAnim(void);

    int fontHandle_ = -1;
    MessageState currentState_ = MessageState::None;

    unsigned int textColor_ = 0;
    unsigned int edgeColor_ = 0;

    enum class AnimPhase {
        FadeIn,
        Stay,
        FadeOut,
    };
    AnimPhase animPhase_ = AnimPhase::FadeIn;

    float animTime_;
    float scaleX_; // メンバ変数の意図を分かりやすくするためsizeからscaleへ名称変更
    float scaleY_;

};
