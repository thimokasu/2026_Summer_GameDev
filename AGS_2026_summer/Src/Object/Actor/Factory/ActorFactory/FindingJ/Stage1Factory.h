#pragma once
#include "../ActorFactoryBase.h"

class Stage1Factory :
    public ActorFactoryBase
{
    public:
    Stage1Factory();
    ~Stage1Factory();
	std::vector<std::shared_ptr<ActorBase>> CreateActors() override;
};

