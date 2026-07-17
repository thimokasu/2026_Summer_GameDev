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
	actors.push_back(std::make_unique<SpikeDropPlayer>());
	//actors.push_back(std::make_unique<Dropper>());
	actors.push_back(std::make_unique<SpikeDropStage>());
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 100, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 200, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 300, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 100, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 200, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 300, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 100, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 200, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 300, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 100, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 200, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 300, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 100, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 200, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 300, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 100, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 200, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 300, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 100, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 200, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 300, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 100, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 200, 0);
	actors.push_back(std::make_unique <Spike>());
	actors.back().get()->GetTransform().pos = VGet(0, 300, 0);
	return actors;
}

