#include "Stage3Factory.h"
#include"../../Stage/FindingJ/Block.h"
#include"../../Stage/FindingJ/ReactionBlock.h"
#include"../../Stage/FindingJ/StageLayout.h"
#include"../../../Common/RigidBody.h"
#include"../../Charactor/FindingJ/FindingJPlayer.h"
#include "../../Stage/FindingJ/Floor.h"

Stage3Factory::Stage3Factory()
{
}

Stage3Factory::~Stage3Factory()
{
}

std::vector<std::unique_ptr<ActorBase>> Stage3Factory::CreateActors(void)
{
	StageLayout layout;
	layout = Stage3::stage[0][0][0];
	std::vector<std::unique_ptr<ActorBase>> actors;

	actors.push_back(
		std::make_unique<FindingJPlayer>());

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
						std::make_unique<Block>(
							VGet(w * TileSize, h * TileSize, d * TileSize)));
					actors.back()->SetEntityKind(EntityKind::STAGE);
					actors.back()->GetRigidBody().SetBodyType(RigidBody::BodyType::STATIC);
				}
				else if (layout == StageLayout::ReactionBlock)
				{
					actors.push_back(
						std::make_unique<ReactionBlock>(
							VGet(w * TileSize, h * TileSize, d * TileSize)));
					actors.back()->SetEntityKind(EntityKind::REACTION_BLOCK);
					actors.back()->GetRigidBody().SetBodyType(RigidBody::BodyType::STATIC);
				}
				else if (layout == StageLayout::Floor)
				{
					actors.push_back(
						std::make_unique<Floor>(
							VGet(w * TileSize, h * TileSize, d * TileSize)));
					actors.back()->SetEntityKind(EntityKind::STAGE);
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
