#include "Dish.h"

void Dish::SubLoad(void)
{
	ContainerBase::SubLoad();
}

void Dish::SubInit(void)
{
	entityKind_ = EntityKind::CONTAINER;
	ContainerBase::SubInit();

}

void Dish::InitSlot(void)
{
	maxSlot_ = 3;
}
