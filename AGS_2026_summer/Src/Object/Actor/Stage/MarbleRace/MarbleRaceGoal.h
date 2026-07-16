#pragma once
#include "../../ActorBase.h"
class MarbleRaceGoal :
    public ActorBase
{
public:
    void SubInit(void)override;
    void SubLoad(void)override;
private:
    void InitRigidBody(void)override;
    void InitCollider(void)override;
};
