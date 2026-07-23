#include "SpikeDropFactory.h"
#include<DxLib.h>
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
	std::unique_ptr<Dropper> dropper;
	dropper = std::make_unique<Dropper>();
	dropper->SetPlayNumber(0);
	dropper->SetUseController(0);
	actors.push_back(std::move(dropper));
	
	for (int i = 1; i <= 4; i++)
	{
		player = std::make_unique<SpikeDropPlayer>();
		player->SetPlayNumber(i);
		player->SetUseController(i);
		player->GetTransform().pos = VGet(-100+i*50, 0, 0);
		actors.push_back(std::move(player));
	}
	actors.push_back(std::make_unique<SpikeDropStage>());
	
	return actors;
}

