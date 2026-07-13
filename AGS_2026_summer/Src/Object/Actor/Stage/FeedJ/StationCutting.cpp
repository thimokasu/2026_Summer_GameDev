#include "StationCutting.h"
#include"../../Collider/ColliderBase.h"

void StationCutting::SubLoad(void)
{
}

void StationCutting::SubInit(void)
{
	for (auto&[shape, col] : ownColliders_)
	{
		col->SetDebugColor(GetColor(100, 200, 180));
	}
	entityKind_ = EntityKind::STATION;
}
