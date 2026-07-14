#pragma once
#include "../ActorFactoryBase.h"
class AthleticFactory :
    public ActorFactoryBase
{
public  :
    AthleticFactory(void);
    ~AthleticFactory(void);
    std::vector<std::unique_ptr<ActorBase>> CreateActors(void)override;
};

