#pragma once

#include<vector>
#include<memory>
#include<unordered_map>


#include"../ActorBase.h"
#include"../../../Scene/GameSelect/GameKind.h"
class ActorFactory
{
public:
	ActorFactory(void);
	~ActorFactory(void);

	std::vector<std::shared_ptr<ActorBase>> CreateActor(GAMEKIND kind);

private:
	std::vector<std::shared_ptr<ActorBase>>actors_;

private:
	Actor CreateFindingJStage1(void);

};
using Actor = std::vector<std::shared_ptr<ActorBase>>;