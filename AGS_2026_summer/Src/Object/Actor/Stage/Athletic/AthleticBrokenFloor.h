#pragma once
#include "../../ActorBase.h"

class AthleticBrokenFloor:public ActorBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;
private:
    void InitRigidBody(void)override;

};

