#pragma once
#include "../../ActorBase.h"
class TestFloor :
    public ActorBase
{
public:

    TestFloor(void);
    TestFloor(VECTOR pos);
    TestFloor(VECTOR pos, VECTOR deg);
    ~TestFloor(void);


    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;

private:
    VECTOR halfSize_ = { 100.0f,10.0f,100.0f };
};

