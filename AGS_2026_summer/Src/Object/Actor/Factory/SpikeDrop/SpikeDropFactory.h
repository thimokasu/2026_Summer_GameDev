#pragma once
#include "../ActorFactoryBase.h"
class SpikeDropFactory :
    public ActorFactoryBase
{
public:
	SpikeDropFactory(void);
	~SpikeDropFactory(void);
	std::vector<std::unique_ptr<ActorBase>> CreateActors(void);
};

