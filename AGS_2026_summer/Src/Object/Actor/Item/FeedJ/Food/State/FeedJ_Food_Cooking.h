#pragma once
#include "../../IFoodState.h"
class FeedJ_Food_Cooking :
    public IFoodState
{
	void Enter(FoodBase* owner);
	void Update(FoodBase* owner);
	void Exit(FoodBase* owner);
};

