#pragma once
#include "../../ActorBase.h"
class SmallMarble :
    public ActorBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
    void InitCollider(void)override;
    void InitRigidBody(void)override;
};

