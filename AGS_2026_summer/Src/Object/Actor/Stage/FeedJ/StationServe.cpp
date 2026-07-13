#include "StationServe.h"
#include"../../Collider/ColliderBase.h"

void StationServe::SubLoad(void)
{
}

void StationServe::SubInit(void)
{
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetDebugColor(GetColor(10, 20, 250));
	}
}
