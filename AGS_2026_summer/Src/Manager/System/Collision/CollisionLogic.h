#pragma once
#include <DxLib.h>
#include <cstdint>
#include "CollisionPairType.h"
#include "CollisionResult.h"
#include "../../../Object/Actor/Collider/ColliderInfo.h"

// 前方宣言
class ColliderBase;

class CollisionLogic
{
public:
	CollisionLogic(void);
	~CollisionLogic(void);

	// 形状からペアタイプを取得
	static CollisionPairType GetCollisionPairType(
		ColliderShape shapeA, ColliderShape shapeB);

	static CollisionResult DispatchCollision(
		CollisionPairType pairType,
		const ColliderBase* colliderA,
		const ColliderBase* colliderB);
private:
	// 球 × 球
	static CollisionResult SphereToSphere(ColliderBase* a, ColliderBase* b);
	// 球 × カプセル
	static CollisionResult SphereToCapsule(ColliderBase* a, ColliderBase* b);
	// 球 × ボックス
	static CollisionResult SphereToBox(ColliderBase* a, ColliderBase* b);
	// カプセル × カプセル
	static CollisionResult CapsuleToCapsule(ColliderBase* a, ColliderBase* b);
	// カプセル × ボックス
	static CollisionResult CapsuleToBox(ColliderBase* a, ColliderBase* b);
	// ボックス × ボックス
	static CollisionResult BoxToBox(ColliderBase* a, ColliderBase* b);
	// 球 × モデル
	static CollisionResult SphereToModel(ColliderBase* a, ColliderBase* b);
	// カプセル × モデル
	static CollisionResult CapsuleToModel(ColliderBase* a, ColliderBase* b);
	// ボックス × モデル
	static CollisionResult BoxToModel(ColliderBase* a, ColliderBase* b);
	// モデル × モデル
	static CollisionResult ModelToModel(ColliderBase* a, ColliderBase* b);
};