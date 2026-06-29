#pragma once
#include "../../ActorBase.h"
class CPU :
    public ActorBase
{
public:
    CPU(void);
    ~CPU(void);
    CPU(VECTOR pos);

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;

private:

    float radius_ = 8.0f;
    VECTOR topPos = { 0.0f, 10.0f, 0.0f };
    VECTOR downPos = { 0.0f, -10.0f, 0.0f };

};



