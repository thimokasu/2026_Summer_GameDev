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
	std::unique_ptr<SpikeDropPlayer> player;
	actors.push_back(std::make_unique<Dropper>());
	for (int i = 1; i <= 4; i++)
	{
		player = std::make_unique<SpikeDropPlayer>();
	}
	actors.push_back(std::make_unique<SpikeDropStage>());
	
	return actors;
}

