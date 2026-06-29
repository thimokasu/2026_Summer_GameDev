#pragma once
#include "../ActorFactoryBase.h"
class Stage :
    public ActorFactoryBase
{
public:
    Stage();
    ~Stage();
    std::vector<std::shared_ptr<ActorBase>> CreateActors() override;
};

