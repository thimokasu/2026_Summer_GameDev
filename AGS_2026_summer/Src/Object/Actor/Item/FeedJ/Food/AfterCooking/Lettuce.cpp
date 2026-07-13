#include "Lettuce.h"

void Lettuce::SubLoad(void)
{
	FoodBase::SubLoad();
}

void Lettuce::SubInit(void)
{
	FoodBase::SubInit();
	entityKind_ = EntityKind::FOOD;
	kind_ = FOOD_KIND::LETTUCE;

}
