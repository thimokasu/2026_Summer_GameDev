#pragma once
#include"../ActorFactoryBase.h"
class Stage3Factory :
    public ActorFactoryBase
{
public:
	Stage3Factory();
	~Stage3Factory();
    std::vector<std::shared_ptr<ActorBase>> CreateActors() override;

};

