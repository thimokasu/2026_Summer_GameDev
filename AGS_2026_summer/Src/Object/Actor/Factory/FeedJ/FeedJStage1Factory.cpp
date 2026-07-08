#include "FeedJStage1Factory.h"
#include"../../Charactor/OneToFour/FeedJ/FeedJPlayer.h"
#include"../../Stage/FeedJ/FeedJStageHeaders.h"
#include"../../Item/FeedJ/FeedJItemHeaders.h"

FeedJStage1Factory::FeedJStage1Factory()
{
}

FeedJStage1Factory::~FeedJStage1Factory()
{
}

std::vector<std::unique_ptr<ActorBase>> FeedJStage1Factory::CreateActors(void)
{
	std::vector<std::unique_ptr<ActorBase>> actors;

	actors.emplace_back(std::make_unique<Tomato>());
	actors.emplace_back(std::make_unique<FeedJPlayer>());
	actors.emplace_back(std::make_unique<FeedJFloor>());

	return actors;
}

