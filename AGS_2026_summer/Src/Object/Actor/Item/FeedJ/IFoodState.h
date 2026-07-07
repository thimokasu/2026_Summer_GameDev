#pragma once
#include<typeindex>

class FoodBase;

class IFoodState
{
public:
	virtual ~IFoodState(void) = default;

	virtual void Enter(FoodBase* owner) = 0;
	virtual void Update(FoodBase* owner) = 0;
	virtual void Exit(FoodBase* owner) = 0;
protected:
	int stateFrame_ = 0;
};