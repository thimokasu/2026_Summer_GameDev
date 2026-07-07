#pragma once
#include "../../ActorBase.h"
class FeedJFloor :
    public ActorBase
{
public  :
    FeedJFloor(void);
    FeedJFloor(VECTOR pos);
    FeedJFloor(VECTOR pos, VECTOR deg);
    FeedJFloor(VECTOR size, VECTOR pos, VECTOR deg);
    ~FeedJFloor(void);


    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;

private:
    VECTOR halfSize_ = { 100.0f,10.0f,100.0f };
};

