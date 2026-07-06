#pragma once
#include "../ActorFactoryBase.h"
class TestFactory :
    public ActorFactoryBase
{
public:
	
	std::vector<std::unique_ptr<ActorBase>> CreateActors(void) override;
};

