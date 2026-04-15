#pragma once
#include<vector>
#include<iostream>

#include"../../../Object/Actor/EntityKind.h"
#include"ContactEventInfo.h"
#include"GameEventType.h"

#include"../../../Object/Actor/ActorBase.h"

class ContactRuleTable
{

public:
	 ContactRule Query(
		ContactRule rule);

private:
	ActorBase actors;
};

