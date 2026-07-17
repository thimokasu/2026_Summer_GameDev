#pragma once
#include "../../ActorBase.h"
class BigMarble :
    public ActorBase
{
    void SubLoad(void)override;
    void SubInit(void)override;
    void InitCollider(void)override;
    void InitRigidBody(void)override;
};

