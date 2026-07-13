#include "StorageCucamber.h"
#include"../../../Collider/ColliderBase.h"

void StorageCucamber::SubLoad(void)
{
}

void StorageCucamber::SubInit(void)
{
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetDebugColor(GetColor(100, 250, 80));
	}
	fKind_ = FOOD_KIND::CUCMBER;
	entityKind_ = EntityKind::STORAGE;
}
