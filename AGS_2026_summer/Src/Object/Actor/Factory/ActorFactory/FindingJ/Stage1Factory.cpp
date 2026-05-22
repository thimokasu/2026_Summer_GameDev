#include "Stage1Factory.h"
#include"../../../Stage/FindingJ/Block.h"
#include"../../../Stage/FindingJ/ReactionBlock.h"
#include"../../../Stage/FindingJ/StageLayout.h"
#include"../../../../Common/RigidBody.h"

Stage1Factory::Stage1Factory()
{
}

Stage1Factory::~Stage1Factory()
{
}

std::vector<std::unique_ptr<ActorBase>> Stage1Factory::CreateActors(void)
{
	StageLayout layout;
	layout = Stage1::stage[0][0][0];
	std::vector<std::unique_ptr<ActorBase>> actors;

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
						std::make_unique<Block>(
							VGet(w * TileSize, h * TileSize, d * TileSize)));
					actors.back()->SetEntityKind(EntityKind::STAGE);
					actors.back()->GetRigidBody().SetBodyType(RigidBody::BodyType::STATIC);
				}
				else if(layout== StageLayout::ReactionBlock)
				{
					actors.push_back(
						std::make_unique<ReactionBlock>(
							VGet(w * TileSize, h * TileSize, d * TileSize)));
					actors.back()->SetEntityKind(EntityKind::REACTION_BLOCK);
					actors.back()->GetRigidBody().SetBodyType(RigidBody::BodyType::STATIC);
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
