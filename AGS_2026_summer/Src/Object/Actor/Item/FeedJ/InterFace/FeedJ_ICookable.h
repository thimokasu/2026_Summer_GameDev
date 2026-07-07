#pragma once
class FeedJ_ICookable
{
public:
	virtual ~FeedJ_ICookable(void) = default;
	virtual void OnCook(void) = 0;
};