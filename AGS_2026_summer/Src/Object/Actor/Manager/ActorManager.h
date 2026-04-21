#pragma once

#include<vector>
#include<memory>
#include<unordered_map>


#include"../ActorBase.h"
#include"../EntityKind.h"

#include "../../../Net/NetStructures.h"

using EntityID = std::uint32_t;


class ActorManager
{

public:

	ActorManager();
	~ActorManager();

	void Load(void);
	std::map<int, NET_JOIN_USER> TestLoad(void);
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

	int entityId_ = 0;
};

