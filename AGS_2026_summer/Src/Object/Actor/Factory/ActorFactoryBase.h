#pragma once
#include<vector>
#include<memory>
#include"../ActorBase.h"

class ActorFactoryBase
{
	public:
	ActorFactoryBase(void) = default;
	virtual ~ActorFactoryBase(void) = default;
	virtual std::vector<std::unique_ptr<ActorBase>> CreateActors(void) = 0;

};