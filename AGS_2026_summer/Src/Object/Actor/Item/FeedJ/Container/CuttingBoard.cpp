#include "CuttingBoard.h"

void CuttingBoard::SubLoad(void)
{
	ContainerBase::SubLoad();
}

void CuttingBoard::SubInit(void)
{
	ContainerBase::SubInit();
	entityKind_ = EntityKind::CONTAINER;
	isPickUp_ = false;
	canCook_ = true;
}

void CuttingBoard::InitSlot(void)
{
	maxSlot_ = 1;
	foods_.resize(maxSlot_);
}
