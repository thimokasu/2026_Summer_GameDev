#include "MiniGameFactory.h"

MiniGameFactory::MiniGameFactory(ActorManager* actMng, CollisionManager* colMng)
{
	actorMng_ = actMng;
	colMng_ = colMng;
}
