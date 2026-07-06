#include "UnicycleFactory.h"
#include<memory>
#include<vector>
#include"../../Shape/Box.h"
#include"../../Shape/Capsule.h"
#include"../../../Common/RigidBody.h"

#include "../../Stage/Unicycle/StageLayout.h"
#include "../../Stage/FindingJ/Block.h"
#include"../../Charactor/OnePlay/Test/TestPlayer.h"




UnicycleFactory::UnicycleFactory()
{
}

std::vector<std::unique_ptr<ActorBase>> UnicycleFactory::CreateActors(void)
{
    std::vector<std::unique_ptr<ActorBase>> actors;

   actors.push_back(std::make_unique<TestPlayer>());
    for (int d = 0; d < D; d++)
    {
        for (int w = 0; w < W; w++)
        {
            if (Stage1::stage[d][w] == StageLayout::Block)
            {
                actors.push_back(
                    std::make_unique<Block>(
                        VGet(w * TileSize, 0.0f, d * TileSize)));
                actors.back()->GetRigidBody().SetBodyType(RigidBody::BodyType::STATIC);
                actors.back()->SetEntityKind(EntityKind::STAGE);
            }
        }
    }
   
 return actors;
}
