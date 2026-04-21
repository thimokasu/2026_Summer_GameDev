#pragma once
#include"../ActorFactoryBase.h"

class Stage2Factory :
    public ActorFactoryBase
{
public:
    Stage2Factory();
    ~Stage2Factory();
    std::vector<std::shared_ptr<ActorBase>> CreateActors() override;
};
