#pragma once
#include"../../Common/Transform.h"

enum class ColliderLayer
{
	NONE = 0,
	CAMERA,
	ACTOR,
	STAGE,

	MAX
};

enum class ColliderShape
{
	NONE,
	LINE,
	SPHERE,
	CAPSULE,
	BOX,
	MODEL,

	MESH,

	TRIANGULAR_PYRAMID,
	TRIANGULAR_PRISM,
	CYLINDER,
	CONE,

	MAX
};

struct ColliderInfo
{
	ColliderShape shape_;// コライダーの形状
	ColliderLayer layer_;// コライダーのレイヤー
	uint32_t mask_;//当たり判定のマスク
	VECTOR localPos_;//ローカル座標
	VECTOR localRot_;//ローカル回転
	bool isTrigger_;//トリガーかどうか
	bool isActive_;//有効かどうか
	int debugColor_ = GetColor(255, 0, 0);//デバッグ用の色
};

using Layer = ColliderLayer;
