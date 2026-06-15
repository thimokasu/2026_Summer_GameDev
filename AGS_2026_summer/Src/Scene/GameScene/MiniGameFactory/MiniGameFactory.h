#pragma once
#include<memory>
#include"../Game/GameBase.h"

class ActorManager;
class CollisionManager;

class MiniGameFactory
{
public:
	MiniGameFactory(ActorManager* actMng, CollisionManager* colMng);
	virtual ~MiniGameFactory(void) = default;
	virtual std::unique_ptr<GameBase>CreateMiniGame(void) = 0;
protected:	
	ActorManager* actorMng_;
	CollisionManager* colMng_;
};