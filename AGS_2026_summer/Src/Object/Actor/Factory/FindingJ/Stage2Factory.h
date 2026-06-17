#pragma once
#include "../ActorFactoryBase.h"
class Stage2Factory :
    public ActorFactoryBase
{
    public:
    Stage2Factory();
    ~Stage2Factory();
	std::vector<std::unique_ptr<ActorBase>> CreateActors(void)override;
};

