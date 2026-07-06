#pragma once
class FeedJ_IPlaceble
{
public:
	virtual ~FeedJ_IPlaceble(void) = default;
	virtual void PlaceItem(void) = 0;
};