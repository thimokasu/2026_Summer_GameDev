#pragma once
#include "../ActorFactoryBase.h"
class FeedJStage1Factory :
    public ActorFactoryBase
{
public  :
    FeedJStage1Factory();
    ~FeedJStage1Factory();
    std::vector<std::unique_ptr<ActorBase>> CreateActors(void)override;
};

