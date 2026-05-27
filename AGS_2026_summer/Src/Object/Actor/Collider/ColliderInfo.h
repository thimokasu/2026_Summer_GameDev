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
	ColliderShape shape_=ColliderShape::SPHERE;// コライダーの形状
	ColliderLayer layer_=ColliderLayer::ACTOR;// コライダーのレイヤー
	uint32_t mask_ = {};//当たり判定のマスク
	VECTOR localPos_ = { 0.0f,0.0f,0.0f };//ローカル座標
	VECTOR localRot_={ 0.0f,0.0f,0.0f };//ローカル回転
	bool isTrigger_=false;//トリガーかどうか
	bool isActive_=true;//有効かどうか
	int debugColor_ = GetColor(255, 0, 0);//デバッグ用の色
};

using Layer = ColliderLayer;
