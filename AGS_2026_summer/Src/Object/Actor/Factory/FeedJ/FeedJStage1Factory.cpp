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
	std::unique_ptr<ContainerBase>container = nullptr;
	actors.emplace_back(std::make_unique<FeedJFloor>());
	actors.emplace_back(std::make_unique<FeedJPlayer>());
	actors.emplace_back(std::make_unique<StorageTomato>());

	station = std::make_unique<StationCutting>();
	station->GetTransform().pos = VGet(100, 10, 100);
	container = std::make_unique<CuttingBoard>();
	container->GetTransform().pos = VGet(100, 40, 100);
	actors.emplace_back(std::move(station));
	actors.emplace_back(std::move(container));

	return actors;
	//STATION_KIND layout;
	//layout = FeedJStage1::station_[0][0];
	//for (int d = 0; d < D; d++)
	//{
	//	for (int w = 0; w < W; w++)
	//	{
	//		layout = FeedJStage1::station_[d][w];
	//		if (layout == STATION_KIND::NORMAL)
	//		{
	//			station = std::make_unique<StationNormal>();
	//			station->SubLoad();
	//			station->SubInit();
	//			station->GetTransform().pos = VGet(w * TileSize, TileSize, d * TileSize);
	//			actors.push_back(std::move(station));
	//		}
	//		else if (layout == STATION_KIND::CUTTING)
	//		{
	//			station = std::make_unique<StationCutting>();
	//			station->SubLoad();
	//			station->SubInit();
	//			station->GetTransform().pos = VGet(w * TileSize, TileSize, d * TileSize);
	//			
	//			container = std::make_unique<CuttingBoard>();
	//			container->SubLoad();
	//			container->SubInit();
	//			container->GetTransform().pos = station->GetTransform().pos;
	//			container->GetTransform().pos.y += 40;
	//			actors.push_back(std::move(station));
	//			actors.push_back(std::move(container));

	//		}
	//		else if (layout == STATION_KIND::DISH)
	//		{
	//			station = std::make_unique<StationDish>();
	//			station->SubLoad();
	//			station->SubInit();
	//			station->GetTransform().pos = VGet(w * TileSize, TileSize, d * TileSize);

	//			container = std::make_unique<Dish>();
	//			container->SubLoad();
	//			container->SubInit();
	//			container->GetTransform().pos = station->GetTransform().pos;
	//			container->GetTransform().pos.y += 40;

	//			actors.push_back(std::move(station));
	//			actors.push_back(std::move(container));
	//		}
	//		else if (layout == STATION_KIND::TRASH)
	//		{
	//			station = std::make_unique<StationTrash>();
	//			station->SubLoad();
	//			station->SubInit();
	//			station->GetTransform().pos = VGet(w * TileSize, TileSize, d * TileSize);
	//			actors.push_back(std::move(station));
	//		}
	//		else if (layout == STATION_KIND::SERVE)
	//		{
	//			station = std::make_unique<StationServe>();
	//			station->SubLoad();
	//			station->SubInit();
	//			station->GetTransform().pos = VGet(w * TileSize, TileSize, d * TileSize);
	//			actors.push_back(std::move(station));
	//		}
	//		else if (layout == STATION_KIND::CUCAMBER)
	//		{
	//			station = std::make_unique <StorageCucamber>();
	//			station->SubLoad();
	//			station->SubInit();
	//			station->GetTransform().pos = VGet(w * TileSize, TileSize, d * TileSize);
	//			actors.push_back(std::move(station));
	//		}
	//		else if (layout == STATION_KIND::TOMATO)
	//		{
	//			station = std::make_unique <StorageTomato>();
	//			station->SubLoad();
	//			station->SubInit();
	//			station->GetTransform().pos = VGet(w * TileSize, TileSize, d * TileSize);
	//			actors.push_back(std::move(station));
	//		}
	//		else if (layout == STATION_KIND::LETTUCE)
	//		{
	//			station = std::make_unique<StorageLettuce>();
	//			station->SubLoad();
	//			station->SubInit();
	//			station->GetTransform().pos = VGet(w * TileSize, TileSize, d * TileSize);
	//			actors.push_back(std::move(station));
	//		}
	//		else { continue; }
	//	}
	//}
	//return actors;
}

