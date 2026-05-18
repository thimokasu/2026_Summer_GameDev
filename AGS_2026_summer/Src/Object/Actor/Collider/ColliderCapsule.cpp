#include "ColliderCapsule.h"

ColliderCapsule::ColliderCapsule(ColliderInfo& info, float radius,
	VECTOR& localPosTop, VECTOR& localPosDown, ActorBase& actor)
	: ColliderBase(info, actor), localPosTop_(localPosTop), localPosDown_(localPosDown), radius_(radius)
{
}

float ColliderCapsule::GetHeight(void) const
{
	return VSize(VSub(localPosTop_, localPosDown_));
}

VECTOR ColliderCapsule::GetPosTop(void) const
{
	return GetRotPos(localPosTop_);
}

VECTOR ColliderCapsule::GetPosDown(void) const
{
	return GetRotPos(localPosDown_);
}

VECTOR ColliderCapsule::GetCenter(void) const
{
	return GetRotPos(VScale(VAdd(localPosTop_, localPosDown_), 0.5f));
}

void ColliderCapsule::DrawDebug(int color)
{
	// 上端と下端のワールド座標を取得
	VECTOR posTop = GetPosTop();
	VECTOR posDown = GetPosDown();
	// カプセルの中心座標を取得
	VECTOR center = GetCenter();
	// 上端と下端を結ぶ線分を描画
	DrawLine3D(posTop, posDown, color);
	// 上端と下端に球を描画
	DrawSphere3D(posTop, radius_, 16, color, color, false);
	DrawSphere3D(posDown, radius_, 16, color, color, false);
	// カプセルの中心に球を描画
	DrawSphere3D(center, radius_, 16, color, color, false);
}