#include "StorageLettuce.h"
#include"../../../Collider/ColliderBase.h"

void StorageLettuce::SubLoad(void)
{
}

void StorageLettuce::SubInit(void)
{
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetDebugColor(GetColor(10, 250, 18));
	}
	fKind_ = FOOD_KIND::LETTUCE;
	entityKind_ = EntityKind::STORAGE;

}
