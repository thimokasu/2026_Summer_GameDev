#include "Stage.h"
#include"../../../Stage/FindingJ/Block.h"
#include"../../../Stage/FindingJ/ReactionBlock.h"
#include"../../../Stage/FindingJ/StageLayout.h"

#include"../../../../../Object/Actor/Component/RigidBodyComponent/RigidBody.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

std::vector<std::shared_ptr<ActorBase>> Stage::CreateActors()
{
    std::vector<std::shared_ptr<ActorBase>> actors;

    for (int d = 0; d < SW::D; d++)
    {
        for (int w = 0; w < SW::W; w++)
        {
            if (StageCircle::stage[d][w] == StageLayout::Block)
            {
                actors.push_back(
                    std::make_shared<Block>(
                        VGet(w * SW::TileSize, 0, d * SW::TileSize)));

                auto rb = std::make_shared<RigidBody>();
                rb->SetBodyType(RigidBody::BodyType::STATIC);

                actors.back()->AddComponent(rb);
                actors.back()->SetEntityKind(EntityKind::STAGE);
            }
        }
    }

    return actors;
}
