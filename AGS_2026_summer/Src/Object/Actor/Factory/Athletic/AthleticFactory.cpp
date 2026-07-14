#include "AthleticFactory.h"
#include"../../Charactor/FourPlayer/Athletic/AthleticPlayer.h"
#include"../../Stage/Athletic/AthleticHeaders.h"
#include"../../Stage/Athletic/AthleticStageKind.h"
#include"../../Stage/Athletic/AthleticStageLayout.h"

AthleticFactory::AthleticFactory(void)
{
}

AthleticFactory::~AthleticFactory(void)
{
}

std::vector<std::unique_ptr<ActorBase>> AthleticFactory::CreateActors(void)
{
    std::vector<std::unique_ptr<ActorBase>> actors;
    std::unique_ptr<ActorBase>stage;
    ATHLETIC_STAGE_KIND layout;
    layout = Athletic::athleticStage[0][0];
    AthleticMoveFloor* mf = nullptr;
    actors.push_back(std::make_unique<AthleticPlayer>());

    for (int d = 0; d < D; d++)
    {
        for (int w = 0; w < W; w++)
        {
            layout = Athletic::athleticStage[d][w];
            switch (layout)
            {
            case ATHLETIC_STAGE_KIND::NONE:
                continue;
                break;
            case ATHLETIC_STAGE_KIND::NORMAL_FLOOR:
                stage = std::make_unique<AthleticNormalFloor>();
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize);
                break;
            case ATHLETIC_STAGE_KIND::BROKEN_FLOOR:
                stage = std::make_unique<AthleticBrokenFloor>();            
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize);
                break;
            case ATHLETIC_STAGE_KIND::MOVE_FLOOR:
                stage = std::make_unique<AthleticMoveFloor>();           
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize);
                mf = dynamic_cast<AthleticMoveFloor*>(stage.get());
                mf->SetStartPos(stage->GetTransform().pos);
                break;
            case ATHLETIC_STAGE_KIND::CLOUD:
                stage = std::make_unique<AthleticCloud>();          
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, -TileSize/2, d * TileSize+TileSize/2);
                break;
            case ATHLETIC_STAGE_KIND::MINI_CLOUD:
                stage = std::make_unique<AthleticMiniCloud>();
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize);
                break;
            case ATHLETIC_STAGE_KIND::SPINBOX:
                stage = std::make_unique<AthleticSpinBox>();         
                
                stage->Load();
                stage->Init();

                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize + TileSize / 2);
                break;
            case ATHLETIC_STAGE_KIND::MINI_SPINBOX:
                stage = std::make_unique<AthleticMiniSpinBox>();          
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize);
                break;
            case ATHLETIC_STAGE_KIND::SPININGBAR:
                stage = std::make_unique<AthleticSpiningBar>();           
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize + TileSize / 2);
                break;
            case ATHLETIC_STAGE_KIND::MINI_SPININGBAR:
                stage = std::make_unique<AthleticMiniSpiningBar>();           
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize);
                break;
            case ATHLETIC_STAGE_KIND::START:
                stage = std::make_unique<AthleticStart>();         
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize);
                break;
            case ATHLETIC_STAGE_KIND::GOAL:
                stage = std::make_unique<AthleticGoal>();            
                stage->Load();
                stage->Init();
                stage->GetTransform().pos = VGet(w * TileSize, 0, d * TileSize);
                break;
            }
            actors.push_back(std::move(stage));
        }
    }
    return actors;
}
