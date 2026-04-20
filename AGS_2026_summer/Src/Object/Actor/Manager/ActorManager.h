#pragma once

#include<vector>
#include<memory>
#include<unordered_map>


#include"../ActorBase.h"
#include"../EntityKind.h"

#include"../ActorFactory/ActorFactory.h"

using EntityID = std::uint32_t;


class ActorManager
{

public:

	ActorManager();
	~ActorManager();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);


	std::vector<std::shared_ptr<ActorBase>> GetActors(void) { return actors_; }
	EntityKind GetKind(int entityId_);

private:
	void BindId2Kind(void);

	std::vector<std::shared_ptr<ActorBase>>actors_;
	std::unordered_map<EntityID, EntityKind>id2Kind_;

	ActorFactory actorFactory_;


	int entityId_ = 0;
};

