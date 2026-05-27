#pragma once
#include "../../ActorBase.h"
class ReactionBlock :
    public ActorBase
{
public:
    ReactionBlock(void);
    ~ReactionBlock(void);
    ReactionBlock(VECTOR pos);

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;

private:
    VECTOR halfSize_ = { 10.0f,10.0f,10.0f };
};
