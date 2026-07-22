#include "SwordFightStage1Factory.h"

#include"../../Stage/SwordFight/StageBlock.h"
#include"../../Stage/SwordFight/SwordFightStageLayOut.h"
#include"../../../Common/RigidBody.h"
#include"../../Charactor/SwordFight/SwordFightPlayer.h"
#include"../../Charactor/SwordFight/SwordFightCPU/SwordFIghtCPU.h"

SwordFightStage1Factory::SwordFightStage1Factory()
{
}

SwordFightStage1Factory::~SwordFightStage1Factory()
{
}

std::vector<std::unique_ptr<ActorBase>> SwordFightStage1Factory::CreateActors(void)
{

	StageLayout layout;
	layout = Stage1::stage[0][0][0];
	std::vector<std::unique_ptr<ActorBase>> actors;

	actors.push_back(
		std::make_unique<SwordFightPlayer>());

	actors.push_back(
		std::make_unique<SwordFIghtCPU>());

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
						std::make_unique<StageBlock>(
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

