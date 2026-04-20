#include "ActorFactory.h"


ActorFactory::ActorFactory(void)
{
}

ActorFactory::~ActorFactory(void)
{
}

Actor CreateFindingJStage1(void)
{
    return Actor();
}


std::vector<std::shared_ptr<ActorBase>> ActorFactory::CreateActor(GAMEKIND kind)
{
    Actor actors;

    switch (kind)
    {
    case GAMEKIND::NONE:
        break;
    case GAMEKIND::FINDINGJ_STAGE1:
        actors = CreateFindingJStage1();
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