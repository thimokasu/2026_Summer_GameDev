#pragma once
#include "../../ActorFactoryBase.h"
#include "../../../../../../Scene/GameSelect/GameKind.h"



class Character :
    public ActorFactoryBase
{
public:
    Character(GameInfo info);
    ~Character();
    std::vector<std::shared_ptr<ActorBase>> CreateActors() override;

private:

    GameInfo info_;
};

