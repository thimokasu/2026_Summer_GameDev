#pragma once
#include "../../ActorBase.h"
class Cliff :
    public ActorBase
{
public:
    Cliff(void);
    ~Cliff(void);
    Cliff(VECTOR pos);

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;

private:
    VECTOR halfSize_ = { 10.0f,80.0f,10.0f };
};

