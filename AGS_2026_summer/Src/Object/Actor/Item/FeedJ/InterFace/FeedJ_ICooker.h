#pragma once
class FeedJ_Cooker
{
public:
	virtual ~FeedJ_Cooker(void) = default;
	virtual void Cook(ActorBase* owner) = 0;
};