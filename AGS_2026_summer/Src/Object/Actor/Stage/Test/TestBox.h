#pragma once
#include "../../ActorBase.h"
class TestBox :
    public ActorBase
{
public:
    TestBox(void);
    TestBox(VECTOR pos);
    ~TestBox(void);

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;

private:
    VECTOR halfSize_ = { 10.0f,10.0f,10.0f };
};