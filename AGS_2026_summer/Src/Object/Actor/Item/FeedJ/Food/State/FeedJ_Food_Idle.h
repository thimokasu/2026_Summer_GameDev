#pragma once
#include "../../IFoodState.h"
class FeedJ_Food_Idle :
    public IFoodState
{
	void Enter(FoodBase* owner);
	void Update(FoodBase* owner);
	void Exit(FoodBase* owner);
};

