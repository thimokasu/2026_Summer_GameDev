#include "ColliderSphere.h"



ColliderSphere::ColliderSphere(ColliderInfo&info,float radius, ActorBase& actor)
	: ColliderBase(info, actor), radius_(radius)
{
}

ColliderSphere::ColliderSphere(ColliderInfo& info, float radius, ActorBase& actor, int debugColor)
	: ColliderBase(info, actor), radius_(radius)
{
	info.debugColor_ = debugColor;
}

void ColliderSphere::DrawDebug(int color)
{
	// ƒ[ƒ‹ƒhÀ•W‚ğæ“¾
	VECTOR pos = GetRotPos(VECTOR{ 0,0,0 });
	// ‹…‚ğ•`‰æ
	DrawSphere3D(pos, radius_, 16, color, color, false);
}