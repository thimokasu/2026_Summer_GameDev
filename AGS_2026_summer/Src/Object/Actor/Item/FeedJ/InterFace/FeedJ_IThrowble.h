#pragma once
#include"../../../ActorBase.h"

class FeedJ_IThrowble
{
public:
	virtual ~FeedJ_IThrowble(void) = default;
	virtual void Throw(ActorBase*owner)=0;
};