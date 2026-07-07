#pragma once
class ActorBase;
class FeedJ_Drop 
{
public:
	virtual ~FeedJ_Drop(void) = default;
	virtual void Drop(ActorBase* target)=0;
};

