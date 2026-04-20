#pragma once

#include<vector>
#include<memory>
#include<unordered_map>


#include"../ActorBase.h"
#include"../../../Scene/GameSelect/GameKind.h"

using Actor = std::vector<std::shared_ptr<ActorBase>>;
class ActorFactory
{
public:
	ActorFactory(void);
	~ActorFactory(void);

	std::vector<std::shared_ptr<ActorBase>> CreateActor(GAMEKIND kind);

private:
	std::vector<std::shared_ptr<ActorBase>>actors_;

private:
	std::vector<std::shared_ptr<ActorBase>> CreateFindingJStage1(Actor actors);

};