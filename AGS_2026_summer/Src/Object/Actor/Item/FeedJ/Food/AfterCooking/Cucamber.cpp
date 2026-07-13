#include "Cucamber.h"

void Cucamber::SubLoad(void)
{
	FoodBase::SubLoad();
}

void Cucamber::SubInit(void)
{
	FoodBase::SubInit();
	entityKind_ = EntityKind::FOOD;
	kind_ = FOOD_KIND::CUCMBER;
}
