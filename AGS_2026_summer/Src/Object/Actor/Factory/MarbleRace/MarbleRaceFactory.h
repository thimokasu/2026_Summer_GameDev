#pragma once
#include "../ActorFactoryBase.h"
class MarbleRaceFactory :
    public ActorFactoryBase
{
public:
    MarbleRaceFactory(void);
    ~MarbleRaceFactory(void);
    std::vector<std::unique_ptr<ActorBase>> CreateActors(void) override;
};

