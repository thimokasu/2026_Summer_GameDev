#pragma once
#include "../ActorFactoryBase.h"

class SwordFightStage1Factory:
    public ActorFactoryBase
{
public:
    SwordFightStage1Factory();
    ~SwordFightStage1Factory();
    std::vector<std::unique_ptr<ActorBase>> CreateActors(void)override;

};

