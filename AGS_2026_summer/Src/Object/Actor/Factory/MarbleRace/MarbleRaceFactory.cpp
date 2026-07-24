#include "MarbleRaceFactory.h"
#include<DxLib.h>
#include"../../Stage/MarbleRace/MarbleRaceFloor.h"
#include"../../Stage/MarbleRace/MarbleRaceGoal.h"
#include"../../Stage/MarbleRace/MarbleRaceWall.h"
#include"../../Charactor/TwoPlay/MarbleRace/MarbleRacePlayer.h"
#include"../../Item/MarbleRace/BigMarble.h"
#include"../../Item/MarbleRace/NormalMarble.h"
#include"../../Item/MarbleRace/SmallMarble.h"
MarbleRaceFactory::MarbleRaceFactory(void)
{
}

MarbleRaceFactory::~MarbleRaceFactory(void)
{
}

std::vector<std::unique_ptr<ActorBase>> MarbleRaceFactory::CreateActors(void)
{
    std::vector<std::unique_ptr<ActorBase>>actors;
    std::unique_ptr<MarbleRacePlayer>player;
    int i = GetJoypadNum();
    for (int i = 0; i < 2; i++)
    {

    player= std::make_unique<MarbleRacePlayer>();
    player->SetPlayNumber(i);
    player->SetUseController(i);
    player->GetTransform().pos = VGet(25 + i * -75, 0, -260);
    actors.push_back(std::move(player));
    }
    actors.push_back(std::make_unique<MarbleRaceFloor>());
    actors.push_back(std::make_unique<MarbleRaceGoal>());
    actors.push_back(std::make_unique<MarbleRaceWall>());

    float minX = -90.0f;
    float maxX = 90.0f;
    float minZ = -200.0f;
    float maxZ = 300.0f;

    for (int i = 0; i < 70; i++)
    {
        // ƒ‰ƒ“ƒ_ƒ€‚ÈˆÊ’u‚ð¶¬‚·‚éƒ‰ƒ€ƒ_Ž®
        auto SetRandomPos = [&](ActorBase* actor) {
            float rx = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
            float rz = minZ + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxZ - minZ)));
            actor->GetTransform().pos = VGet(rx, i , rz);
            };

        // SmallMarble
        actors.push_back(std::make_unique<SmallMarble>());
        SetRandomPos(actors.back().get());

        // NormalMarble
        actors.push_back(std::make_unique<NormalMarble>());
        SetRandomPos(actors.back().get());

        // BigMarble
        actors.push_back(std::make_unique<BigMarble>());
        SetRandomPos(actors.back().get());
    }

    return actors;
}