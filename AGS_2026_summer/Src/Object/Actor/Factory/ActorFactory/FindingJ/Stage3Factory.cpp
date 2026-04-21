#include "Stage3Factory.h"
#include"../../../Stage/FindingJ/Block.h"
#include"../../../Stage/FindingJ/ReactionBlock.h"
#include"../../../Stage/FindingJ/StageLayout.h"

#include"../../../../../Object/Actor/Component/RigidBodyComponent/RigidBody.h"

Stage3Factory::Stage3Factory()
{
}

Stage3Factory::~Stage3Factory()
{
}

std::vector<std::shared_ptr<ActorBase>> Stage3Factory::CreateActors()
{
	StageLayout layout;
	auto rb = std::make_shared<RigidBody>();
	rb->SetBodyType(RigidBody::BodyType::STATIC);

	std::vector<std::shared_ptr<ActorBase>>actors;

	for (int h = 0; h < H; h++)
	{
		for (int d = 0; d < D; d++)
		{
			for (int w = 0; w < W; w++)
			{
				layout = Stage3::stage[h][d][w];
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
					actors.back()->SetEntityKind(EntityKind::REACTION_BLOCK);
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
