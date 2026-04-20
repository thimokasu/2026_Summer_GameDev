#include "ActorFactory.h"

#include"../Stage/FindingJ/StageLayout.h"
#include"../Stage/FindingJ/Block.h"
#include"../Stage/FindingJ/ReactionBlock.h"

#include"../../../Object/Actor/Component/RigidBodyComponent/RigidBody.h"

ActorFactory::ActorFactory(void)
{
}

ActorFactory::~ActorFactory(void)
{
}



std::vector<std::shared_ptr<ActorBase>> ActorFactory::CreateActor(GAMEKIND kind)
{
    Actor actors;

    switch (kind)
    {
    case GAMEKIND::NONE:
        break;
    case GAMEKIND::FINDINGJ_STAGE1:
        actors = CreateFindingJStage1(actors);
        break;
    case GAMEKIND::FINDINGJ_STAGE2:
        break;
    case GAMEKIND::FINDINGJ_STAGE3:
        break;
    default:
        break;
    }
    return actors;
}

std::vector<std::shared_ptr<ActorBase>> ActorFactory::CreateFindingJStage1(Actor actors)
{
    Stage1::stage;
    StageLayout layout;
	layout = Stage1::stage[0][0][0];

	auto rb = std::make_shared<RigidBody>();
	rb->SetBodyType(RigidBody::BodyType::STATIC);


    for (int h = 0; h < H; h++)
    {
        for (int d = 0; d < D; d++)
        {
            for (int w = 0; w < W; w++)
            {
                layout = Stage1::stage[h][d][w];
                if (layout == StageLayout::Block)
                {
                    actors.push_back(
                        std::make_shared<Block>(
                            VGet(w * TileSize, h * TileSize, d * TileSize)));
					actors.back()->AddComponent(rb);
					actors.back()->SetEntityKind(EntityKind::STAGE);
                }
                else if (layout == StageLayout::ReactionBlock)
                {
                    actors.push_back(
                        std::make_shared<ReactionBlock>(
                            VGet(w * TileSize, h * TileSize, d * TileSize)));
                    actors.back()->AddComponent(rb);
                    actors.back()->SetEntityKind(EntityKind::STAGE);
                }
                else
				{
					continue;
                }
            }
        }
	}
    return actors;
}


