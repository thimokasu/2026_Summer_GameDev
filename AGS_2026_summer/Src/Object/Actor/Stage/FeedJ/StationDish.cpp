#include "StationDish.h"
#include"../../Collider/ColliderBase.h"

void StationDish::SubLoad(void)
{
}

void StationDish::SubInit(void)
{
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetDebugColor(GetColor(200, 100, 180));
	}
}
