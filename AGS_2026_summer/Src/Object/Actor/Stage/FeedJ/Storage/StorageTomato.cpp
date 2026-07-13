#include "StorageTomato.h"
#include"../../../Collider/ColliderBase.h"

void StorageTomato::SubLoad(void)
{
}

void StorageTomato::SubInit(void)
{
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetDebugColor(GetColor(150, 20, 18));
	}
	fKind_ = FOOD_KIND::TOMATO;
	entityKind_ = EntityKind::STORAGE;

}
