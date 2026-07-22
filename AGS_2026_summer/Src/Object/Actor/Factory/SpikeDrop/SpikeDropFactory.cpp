#include "SpikeDropFactory.h"
#include"../../Charactor/OneVsThree/SpikeDrop/SpikeDropPlayer.h"
#include"../../Charactor/OneVsThree/SpikeDrop/Dropper.h"
#include"../../Item/SpikeDrop/Spike.h"
#include"../../Stage/SpikeDrop/SpikeDropStage.h"

SpikeDropFactory::SpikeDropFactory(void)
{
}

SpikeDropFactory::~SpikeDropFactory(void)
{
}

std::vector<std::unique_ptr<ActorBase>> SpikeDropFactory::CreateActors(void)
{
	std::vector<std::unique_ptr<ActorBase>>actors;
	actors.push_back(std::make_unique<Dropper>());
	actors.push_back(std::make_unique<SpikeDropPlayer>());
	actors.push_back(std::make_unique<SpikeDropStage>());
	
	return actors;
}

