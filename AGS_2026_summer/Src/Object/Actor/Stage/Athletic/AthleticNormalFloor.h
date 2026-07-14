#pragma once
#include "../../ActorBase.h"
class AthleticNormalFloor :
    public ActorBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

private:
    void InitCollider(void)override;
    void InitRigidBody(void)override;

};

