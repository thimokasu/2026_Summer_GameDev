#include "Dish.h"

void Dish::SubLoad(void)
{
	ContainerBase::SubLoad();
}

void Dish::SubInit(void)
{
	entityKind_ = EntityKind::CONTAINER;
	ContainerBase::SubInit();
	trans_.pos = VGet(-100, 100, -100);
	maxSlot_ = 1;
}

void Dish::InitSlot(void)
{
	maxSlot_ = 3;
}
