#pragma once
#include "../../ActorBase.h"
class ReactionBlock :
    public ActorBase
{
public:


    ReactionBlock();
    ReactionBlock(VECTOR pos);

	~ReactionBlock();

    void OnContact(std::shared_ptr<ActorBase> other) {
        // 踏まれたら、自分自身の発光タイマーをセットする
        glowTimer_ = 0.5f;
    }

    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
	void InitCollider(void) override;

    // 踏まれたときに呼ばれる関数
    void ActivateGlow() {
        isGlowing_ = true;
        glowTimer_ = GLOW_DURATION;
    }


private:
    VECTOR halfSize_ = { 10.0f,10.0f,10.0f };

    bool isGlowing_ = false;      // 今光っているか
    float glowTimer_ = 0.0f;     // 残り発光時間
    const float GLOW_DURATION = 2.0f; // 何秒間光らせるか

};

