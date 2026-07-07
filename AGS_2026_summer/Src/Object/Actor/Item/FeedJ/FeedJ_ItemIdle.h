#pragma once
#include "IFoodState.h"
class FeedJ_ItemIdle :
    public IFoodState
{
public:

	void Enter(FoodBase* owner)override;
	void Update(FoodBase* owner)override;
	void Exit(FoodBase* owner)override;
};

