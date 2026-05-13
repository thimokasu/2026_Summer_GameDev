#pragma once
#include "../../ActorBase.h"
class ReactionBlock :
    public ActorBase
{
public:


    ReactionBlock();
    ReactionBlock(VECTOR pos);

	~ReactionBlock();


    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
	void InitCollider(void) override;

    // “¥‚Ü‚ê‚½‚Æ‚«‚ÉŒÄ‚Î‚ê‚éŠÖ”
    void ActivateGlow() {
        isGlowing_ = true;
        glowTimer_ = GLOW_DURATION;
    }


private:
    VECTOR halfSize_ = { 10.0f,10.0f,10.0f };

    bool isGlowing_ = false;      // ¡Œõ‚Á‚Ä‚¢‚é‚©
    float glowTimer_ = 0.0f;     // c‚è”­ŒõŠÔ
    const float GLOW_DURATION = 2.0f; // ‰½•bŠÔŒõ‚ç‚¹‚é‚©

};

