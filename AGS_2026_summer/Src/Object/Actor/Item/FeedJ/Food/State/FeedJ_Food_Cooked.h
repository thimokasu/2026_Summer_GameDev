#pragma once
#include "../../IFoodState.h"
#include"../FoodBase.h"
class FeedJ_Food_Cooked :
    public IFoodState
{
	void Enter(FoodBase* owner);
	void Update(FoodBase* owner);
	void Exit(FoodBase* owner);
};

