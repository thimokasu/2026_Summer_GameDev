#pragma once
class FeedJ_ICookable
{
	virtual ~FeedJ_ICookable(void) = default;
	virtual void OnCook(void) = 0;
};