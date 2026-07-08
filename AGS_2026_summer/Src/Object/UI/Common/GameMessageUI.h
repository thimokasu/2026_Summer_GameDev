#pragma once
#include "../UIBase.h"
#include<functional>
#include<string>
#include<unordered_map>
using StartCallBack = std::function<void()>;
class GameMessageUI : public UIBase
{
public:
    static constexpr int FontSize = 100;
    static constexpr int EdgeSize = 4;

    static constexpr const char* StrStart = "START!";
    static constexpr const char* StrFinish = "FINISH!";
    static constexpr const char* StrExplain = "FIND J";
    static constexpr const char* StrNone = "";

    enum class MASSAGE_STATE
    {
        NONE,
        EXPLAIN,
        START,
        FINISH,
    };

    enum class ANIM_PHASE
    {
        NONE=-1,
        FADE_IN,
        STAY,
        FADE_OUT
    };

    // UIBaseのコンストラクタに合わせる
    GameMessageUI(Vector2F pos, Vector2F size);
    virtual ~GameMessageUI() = default;

    void SetStartCallBack(StartCallBack callBack) { startCallBack_ = std::move(callBack); }
    void SetMassageState(MASSAGE_STATE state);

    void SetMassageText(MASSAGE_STATE state, const std::string& text);

private:
    // UIBaseの仮想関数をオーバーライド
    void SubLoad() override;
    void SubInit() override;
    void SubUpdate() override;
    void SubDraw() override;
    void SubRelease() override;

    void TextAnim(void);

#pragma region 変数
    // 状態ごとのテキストを保持するマップ
    std::unordered_map<MASSAGE_STATE, std::string> messageMap_;
    std::string currentText_ = "";

    int fontHandle_ = -1;
    MASSAGE_STATE currentState_ = MASSAGE_STATE::EXPLAIN;
    int textColor_ = 0;
    int edgeColor_ = 0;
    ANIM_PHASE animPhase_ = ANIM_PHASE::FADE_IN;

    float animTime_;
    float scaleX_;
    float scaleY_;
    StartCallBack startCallBack_=nullptr;

#pragma endregion


};