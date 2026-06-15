#pragma once
#include"../MiniGameFactory.h"

class FindingJFactory :public MiniGameFactory
{
public:
    FindingJFactory(ActorManager* actMng,CollisionManager* colMng);
    std::unique_ptr<GameBase>CreateMiniGame(void);
};

