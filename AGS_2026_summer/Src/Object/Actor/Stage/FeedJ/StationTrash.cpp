#include "StationTrash.h"
#include"../../Collider/ColliderBase.h"

void StationTrash::SubLoad(void)
{
}

void StationTrash::SubInit(void)
{
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetDebugColor(GetColor(10, 200, 18));
	}
}
