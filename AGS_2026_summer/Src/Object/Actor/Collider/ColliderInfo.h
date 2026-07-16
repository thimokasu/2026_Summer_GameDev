#pragma once
#include"../../Common/Transform.h"
#include"../../Actor/EntityKind.h"
enum class ColliderLayer
{
	NONE = 0,
	CAMERA,
	ACTOR,
	ACTOR_TRIGGER,
	STAGE,

	//FeedJ
	FOOD,
	STATION,
	CONTAINER,

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
	EntityKind entityKind_ = EntityKind::NONE;	//コライダーの種類（アクターを参照、トリガーの場合トリガー用のEntityKindを新たに定義）
	uint32_t mask_ = {};//当たり判定のマスク
	VECTOR localPos_ = { 0.0f,0.0f,0.0f };//ローカル座標
	VECTOR localRot_={ 0.0f,0.0f,0.0f };//ローカル回転
	bool isTrigger_=false;//トリガーかどうか
	bool isActive_=true;//有効かどうか
	int debugColor_ = GetColor(255, 0, 0);//デバッグ用の色
	bool isDraw_ = true;
};

using Layer = ColliderLayer;
