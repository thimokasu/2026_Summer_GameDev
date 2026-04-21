#pragma once

#include<vector>
#include<memory>
#include<unordered_map>


#include"../ActorBase.h"
#include"../EntityKind.h"
#include"../../../Scene/GameSelect/GameKind.h"

using EntityID = std::uint32_t;
class ActorFactoryBase;

class ActorManager
{

public:

	ActorManager();
	~ActorManager();

	void Load(void);
	void Load(GameInfo info);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);


	std::vector<std::shared_ptr<ActorBase>> GetActors(void) { return actors_; }
	EntityKind GetKind(int entityId_);

private:

	std::vector<std::shared_ptr<ActorBase>>actors_;
	std::unordered_map<EntityID, EntityKind>id2Kind_;

	std::unique_ptr<ActorFactoryBase>actorFactory_;


	int entityId_ = 0;
private	:
	void BindId2Kind(void);
	void SetFactory(GameInfo info);
};

