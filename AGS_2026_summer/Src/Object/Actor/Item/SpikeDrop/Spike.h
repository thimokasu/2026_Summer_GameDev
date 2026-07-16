#pragma once
#include "../ItemBase.h"
class Spike :
    public ItemBase
{
public:
    Spike(void);
    ~Spike(void);

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

private:
    void InitCollider(void)override;
    void InitRigidBody(void)override;
};

