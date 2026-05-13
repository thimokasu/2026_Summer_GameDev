#pragma once
#include<vector>
#include<memory>
#include"CollisionSystem.h"
class ActorBase;

class CollisionResolve
{
public:
	CollisionResolve();
	~CollisionResolve();

	void Resolve(const std::vector<std::shared_ptr<ActorBase>>& objects, std::vector<CollisionSystem::CollisionManifold>mainfold);


};

