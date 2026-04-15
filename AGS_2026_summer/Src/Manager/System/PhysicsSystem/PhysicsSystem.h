#pragma once
#include<vector>
#include<memory>
#include"../CollisionSystem/CollisionSystem.h"

class ActorBase;

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void Update(const std::vector<std::shared_ptr<ActorBase>>& objects);
	

	//ç≈èIà íuåàíË
	void Resolve(const std::vector<std::shared_ptr<ActorBase>>& objects,std::vector<CollisionSystem::CollisionManifold> mainfold);
private:
};

