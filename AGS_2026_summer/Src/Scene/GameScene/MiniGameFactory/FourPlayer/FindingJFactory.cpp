#include "FindingJFactory.h"
#include"../../Game/FourPlayer/FindingJ.h"
#include"../../../../Manager/System/Collision/CollisionManager.h"
#include"../../../../Object/Actor/Manager/ActorManager.h"

FindingJFactory::FindingJFactory(ActorManager* actMng, CollisionManager* colMng)
	:
	MiniGameFactory(actMng,colMng)
{

}

std::unique_ptr<GameBase> FindingJFactory::CreateMiniGame(void)
{
	auto g=std::make_unique<FindingJ>(actorMng_, colMng_);
	return g;
}

