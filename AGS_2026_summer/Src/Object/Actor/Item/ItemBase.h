#pragma once
#include "../ActorBase.h"
class ItemBase :
    public ActorBase
{
    public:
    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;
    void InitCollider(void)override;
protected:
};

