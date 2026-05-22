#pragma once
#include "../ActorFactoryBase.h"
class Stage1Factory :
    public ActorFactoryBase
{
public:
    Stage1Factory();
    ~Stage1Factory();
    std::vector<std::unique_ptr<ActorBase>> CreateActors(void)override;
};

