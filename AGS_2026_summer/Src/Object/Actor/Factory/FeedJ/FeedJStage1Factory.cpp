#include "FeedJStage1Factory.h"
#include"../../Charactor/OneToFour/FeedJ/FeedJPlayer.h"
#include"../../Stage/FeedJ/FeedJStageHeaders.h"
#include"../../Item/FeedJ/FeedJItemHeaders.h"
#include"../../Stage/FeedJ/FeedJStageLayout.h"

FeedJStage1Factory::FeedJStage1Factory()
{
}

FeedJStage1Factory::~FeedJStage1Factory()
{
}

std::vector<std::unique_ptr<ActorBase>> FeedJStage1Factory::CreateActors(void)
{
	std::vector<std::unique_ptr<ActorBase>> actors;
	std::unique_ptr<StationBase> station = nullptr;
	actors.emplace_back(std::make_unique<FeedJFloor>());
	actors.emplace_back(std::make_unique<FeedJPlayer>());

	STATION_KIND layout;
	layout = FeedJStage1::station_[0][0];
	for (int d = 0; d < D; d++)
	{
		for (int w = 0; w < W; w++)
		{
			layout = FeedJStage1::station_[d][w];
			if (layout == STATION_KIND::NORMAL)
			{
				station = std::make_unique<StationNormal>();
				station->Load();
				station->Init();
				station->GetTransform().pos = VGet(w * TileSize, TileSize, d * TileSize);
				actors.push_back(std::move(station));
			}
			else if (layout == STATION_KIND::CUTTING)
			{
			}
			else if (layout == STATION_KIND::DISH)
			{

			}
			else if (layout == STATION_KIND::TRASH)
			{
			}
			else if (layout == STATION_KIND::CUCAMBER)
			{
			}
			else if (layout == STATION_KIND::TOMATO)
			{
			}
			else if (layout == STATION_KIND::LETTUCE)
			{
			}
			else { continue; }
		}
	}
	return actors;
}

