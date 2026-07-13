#include "Tomato.h"

void Tomato::SubLoad(void)
{
	FoodBase::SubLoad();
}

void Tomato::SubInit(void)
{
	FoodBase::SubInit();
	entityKind_ = EntityKind::FOOD;
	kind_ = FOOD_KIND::TOMATO;

}
