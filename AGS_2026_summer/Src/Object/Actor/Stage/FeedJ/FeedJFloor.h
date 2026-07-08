#pragma once
#include "../../ActorBase.h"
class FeedJFloor :
    public ActorBase
{
public  :
    FeedJFloor(void);
    FeedJFloor(VECTOR pos);
    FeedJFloor(VECTOR pos, VECTOR size);
    FeedJFloor( VECTOR pos, VECTOR size, VECTOR deg = VGet(0, 0, 0));
    ~FeedJFloor(void);


    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;

private:
    VECTOR halfSize_ = { 1000.0f,10.0f,1000.0f };
};

