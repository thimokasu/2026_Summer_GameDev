#include "UnicycleFactory.h"
#include<memory>
#include<vector>
#include"../../Shape/Box.h"
#include"../../Shape/Capsule.h"
#include"../../../Common/RigidBody.h"

#include "../../Stage/Unicycle/StageLayout.h"
#include "../../Stage/FindingJ/Block.h"
#include"../../Charactor/OnePlay/Test/TestPlayer.h"
#include "../../Charactor/OnePlay/Unicycle/UnicyclePlayer.h"
#include "../../Stage/Unicycle/Cliff.h"
#include "../../../../Manager/Game/SceneManager.h"



UnicycleFactory::UnicycleFactory()
{
    multiOffset_ = 250.0f;
}

std::vector<std::unique_ptr<ActorBase>> UnicycleFactory::CreateActors(void)
{
    std::vector<std::unique_ptr<ActorBase>> actors;

    int playerNum = SceneManager::GetInstance().GetPlayerNum(GAME_KIND::UNICYCLE);
    for (int i = 0; i < playerNum; i++)
    {
        actors.push_back(std::make_unique<UnicyclePlayer>(VGet(30.0f+ multiOffset_ * i, 30.0f, 0.0f),i));
        for (int d = 0; d < D; d++)
        {
            for (int w = 0; w < W; w++)
            {
                if (Stage1::stage[d][w] == StageLayout::Block)
                {
                    actors.push_back(
                        std::make_unique<Cliff>(
                            VGet(w * TileSize+ multiOffset_ *i, 0.0f, d * TileSize)));
                    actors.back()->GetRigidBody().SetBodyType(RigidBody::BodyType::STATIC);
                }
            }
        }
    }


   
 return actors;
}
