#include "CollisionLogic.h"
#include <algorithm>
#include <cmath>
#include "../../../Object/Actor/Collider/ColliderInfo.h"
#include "../../../Object/Actor/Collider/ColliderBase.h"

#include "../../../Object/Actor/Collider/ColliderSphere.h"
#include "../../../Object/Actor/Collider/ColliderBox.h"
#include "../../../Object/Actor/Collider/ColliderCapsule.h"

CollisionLogic::CollisionLogic(void)
{
}

CollisionLogic::~CollisionLogic(void)
{
}

CollisionPairType CollisionLogic::GetCollisionPairType(ColliderShape shapeA, ColliderShape shapeB)
{
	// 同じ形状同士  
	if (shapeA == shapeB)
	{
		switch (shapeA)
		{
		case ColliderShape::SPHERE:  return CollisionPairType::SPHERE_SPHERE;
		case ColliderShape::CAPSULE: return CollisionPairType::CAPSULE_CAPSULE;
		case ColliderShape::BOX:     return CollisionPairType::BOX_BOX;
		default:                     return CollisionPairType::NONE;
		}
	}

	// 順序を吸収（小さいほうをAに）  
	if (shapeA > shapeB)
		std::swap(shapeA, shapeB);

	// 異なる形状同士  
	if (shapeA == ColliderShape::SPHERE && shapeB == ColliderShape::CAPSULE)
		return CollisionPairType::SPHERE_CAPSULE;

	if (shapeA == ColliderShape::SPHERE && shapeB == ColliderShape::BOX)
		return CollisionPairType::SPHERE_BOX;

	if (shapeA == ColliderShape::CAPSULE && shapeB == ColliderShape::BOX)
		return CollisionPairType::CAPSULE_BOX;

	if (shapeA == ColliderShape::SPHERE && shapeB == ColliderShape::MODEL)
		return CollisionPairType::SPHERE_MODEL;

	if (shapeA == ColliderShape::CAPSULE && shapeB == ColliderShape::MODEL)
		return CollisionPairType::CAPSULE_MODEL;

	if (shapeA == ColliderShape::BOX && shapeB == ColliderShape::MODEL)
		return CollisionPairType::BOX_MODEL;

	if (shapeA == ColliderShape::MODEL && shapeB == ColliderShape::MODEL)
		return CollisionPairType::MODEL_MODEL;

	return CollisionPairType::NONE;
}

CollisionResult CollisionLogic::DispatchCollision(CollisionPairType pairType, const ColliderBase* a, const ColliderBase* b)
{
	CollisionResult result;
	switch (pairType)
	{
	case CollisionPairType::NONE:
		break;
	case CollisionPairType::SPHERE_SPHERE:
		result = SphereToSphere(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	case CollisionPairType::SPHERE_CAPSULE:
		result = SphereToCapsule(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	case CollisionPairType::SPHERE_BOX:
		result = SphereToBox(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	case CollisionPairType::CAPSULE_CAPSULE:
		result = CapsuleToCapsule(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	case CollisionPairType::CAPSULE_BOX:
		result = CapsuleToBox(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	case CollisionPairType::BOX_BOX:
		result = BoxToBox(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	case CollisionPairType::SPHERE_MODEL:
		result = SphereToModel(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	case CollisionPairType::CAPSULE_MODEL:
		result = CapsuleToModel(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	case CollisionPairType::BOX_MODEL:
		result = BoxToModel(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	case CollisionPairType::MODEL_MODEL:
		result = ModelToModel(const_cast<ColliderBase*>(a), const_cast<ColliderBase*>(b));
		break;
	default:
		break;
	}
	return result;
}

// 1. 球 × 球
// 1. 球 × 球
CollisionResult CollisionLogic::SphereToSphere(ColliderBase* a, ColliderBase* b)
{
	CollisionResult result;
	auto sphereA = dynamic_cast<ColliderSphere*>(a);
	auto sphereB = dynamic_cast<ColliderSphere*>(b);

	if (!sphereA || !sphereB) return result;

	VECTOR posA = sphereA->GetOwnerTransform().pos;
	VECTOR posB = sphereB->GetOwnerTransform().pos;
	float radiusSum = sphereA->GetRadius() + sphereB->GetRadius();

	VECTOR diff = VSub(posA, posB);
	float distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

	if (distSq > radiusSum * radiusSum) return result;

	result.isHit = true;
	if (distSq < 0.0001f) {
		result.normal = VGet(0.0f, 1.0f, 0.0f);
		result.penetration = radiusSum;
		// 重なっている場合は、とりあえずAの中心点
		result.contactPoint = posA;
	}
	else {
		float dist = sqrtf(distSq);
		result.normal = VScale(diff, 1.0f / dist);
		result.penetration = radiusSum - dist;

		// ★追加：球Aの表面と球Bの表面のめり込んでいる中間地点を接触点とする
		VECTOR pointA = VSub(posA, VScale(result.normal, sphereA->GetRadius()));
		VECTOR pointB = VAdd(posB, VScale(result.normal, sphereB->GetRadius()));
		result.contactPoint = VScale(VAdd(pointA, pointB), 0.5f); // 中点
	}
	return result;
}
// 2. 球 × カプセル
CollisionResult CollisionLogic::SphereToCapsule(ColliderBase* a, ColliderBase* b)
{
	CollisionResult result;
	auto sphere = dynamic_cast<ColliderSphere*>(a);
	auto capsule = dynamic_cast<ColliderCapsule*>(b);

	bool swapped = false;
	if (!sphere) {
		sphere = dynamic_cast<ColliderSphere*>(b);
		capsule = dynamic_cast<ColliderCapsule*>(a);
		swapped = true;
	}
	if (!sphere || !capsule) return result;

	VECTOR sPos = sphere->GetOwnerTransform().pos;
	VECTOR capA = capsule->GetPosDown();
	VECTOR capB = capsule->GetPosTop();

	VECTOR ab = VSub(capB, capA);
	VECTOR ap = VSub(sPos, capA);
	float l2 = VDot(ab, ab);
	float t = (l2 > 0.0f) ? VDot(ap, ab) / l2 : 0.0f;
	t = fmaxf(0.0f, fminf(1.0f, t));
	VECTOR nearestP = VAdd(capA, VScale(ab, t));

	VECTOR diff = VSub(sPos, nearestP);
	float distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	float radiusSum = sphere->GetRadius() + capsule->GetRadius();

	if (distSq > radiusSum * radiusSum) return result;

	result.isHit = true;
	VECTOR finalNormal;
	if (distSq < 0.0001f) {
		finalNormal = VGet(0.0f, 1.0f, 0.0f);
		result.penetration = radiusSum;
		// 完全に重なっている場合は、球の中心を暫定の接触点とする
		result.contactPoint = sPos;
	}
	else {
		float dist = sqrtf(distSq);
		finalNormal = VScale(diff, 1.0f / dist);
		result.penetration = radiusSum - dist;

		// ★追加：球の表面とカプセルの表面がめり込んでいる中間地点を接触点とする
		VECTOR pointOnSphere = VSub(sPos, VScale(finalNormal, sphere->GetRadius()));
		VECTOR pointOnCapsule = VAdd(nearestP, VScale(finalNormal, capsule->GetRadius()));
		result.contactPoint = VScale(VAdd(pointOnSphere, pointOnCapsule), 0.5f);
	}

	result.normal = swapped ? VScale(finalNormal, -1.0f) : finalNormal;
	return result;
}

// 3. 球 × ボックス
CollisionResult CollisionLogic::SphereToBox(ColliderBase* a, ColliderBase* b)
{
	CollisionResult result;
	auto sphere = dynamic_cast<ColliderSphere*>(a);
	auto box = dynamic_cast<ColliderBox*>(b);

	bool swapped = false;
	if (!sphere) {
		sphere = dynamic_cast<ColliderSphere*>(b);
		box = dynamic_cast<ColliderBox*>(a);
		swapped = true;
	}
	if (!sphere || !box) return result;

	VECTOR sWorldPos = sphere->GetOwnerTransform().pos;
	VECTOR sLocalPos = box->World2Local(sWorldPos);
	VECTOR bHalfSize = box->GetHalfSize();

	VECTOR closestLocalP;
	closestLocalP.x = fmaxf(-bHalfSize.x, fminf(sLocalPos.x, bHalfSize.x));
	closestLocalP.y = fmaxf(-bHalfSize.y, fminf(sLocalPos.y, bHalfSize.y));
	closestLocalP.z = fmaxf(-bHalfSize.z, fminf(sLocalPos.z, bHalfSize.z));

	VECTOR diffLocal = VSub(sLocalPos, closestLocalP);
	float distSq = diffLocal.x * diffLocal.x + diffLocal.y * diffLocal.y + diffLocal.z * diffLocal.z;
	float sRadius = sphere->GetRadius();

	if (distSq > sRadius * sRadius) return result;

	result.isHit = true;
	VECTOR worldPointOnBox = box->Local2World(closestLocalP);
	VECTOR finalNormal; // ★ここでローカル変数として正しく定義

	if (distSq < 0.0001f) {
		finalNormal = box->GetAxisY();
		result.penetration = sRadius;
		result.contactPoint = sWorldPos; // 重なっている場合は球の中心
	}
	else {
		float dist = sqrtf(distSq);
		finalNormal = VScale(VSub(sWorldPos, worldPointOnBox), 1.0f / dist);
		result.penetration = sRadius - dist;
		result.contactPoint = worldPointOnBox; // ボックス上の最接近点を接触点とする
	}

	result.normal = swapped ? VScale(finalNormal, -1.0f) : finalNormal;
	return result;
}

// 4. カプセル × カプセル
CollisionResult CollisionLogic::CapsuleToCapsule(ColliderBase* a, ColliderBase* b)
{
	CollisionResult result;
	auto capA = dynamic_cast<ColliderCapsule*>(a);
	auto capB = dynamic_cast<ColliderCapsule*>(b);

	if (!capA || !capB) return result;

	VECTOR p1 = capA->GetPosDown();
	VECTOR q1 = capA->GetPosTop();
	float r1 = capA->GetRadius();

	VECTOR p2 = capB->GetPosDown();
	VECTOR q2 = capB->GetPosTop();
	float r2 = capB->GetRadius();

	VECTOR d1 = VSub(q1, p1);
	VECTOR d2 = VSub(q2, p2);
	VECTOR r = VSub(p1, p2);

	float a_len = VDot(d1, d1);
	float e = VDot(d2, d2);
	float f = VDot(d2, r);

	float s = 0.0f;
	float t = 0.0f;

	float b_val = VDot(d1, d2);
	float c = VDot(d1, r);
	float den = a_len * e - b_val * b_val;

	if (den != 0.0f) {
		s = fmaxf(0.0f, fminf((b_val * f - c * e) / den, 1.0f));
	}
	else {
		s = 0.0f;
	}

	t = (b_val * s + f) / e;

	if (t < 0.0f) {
		t = 0.0f;
		s = fmaxf(0.0f, fminf(-c / a_len, 1.0f));
	}
	else if (t > 1.0f) {
		t = 1.0f;
		s = fmaxf(0.0f, fminf((b_val - c) / a_len, 1.0f));
	}

	VECTOR closestP1 = VAdd(p1, VScale(d1, s));
	VECTOR closestP2 = VAdd(p2, VScale(d2, t));

	VECTOR diff = VSub(closestP1, closestP2);
	float distSq = VDot(diff, diff);
	float radiusSum = r1 + r2;

	if (distSq > radiusSum * radiusSum) return result;

	result.isHit = true;
	if (distSq < 0.0001f) {
		result.normal = VGet(0.0f, 1.0f, 0.0f);
		result.penetration = radiusSum;
		// 完全に重なっている場合は、カプセルAの最接近点
		result.contactPoint = closestP1;
	}
	else {
		float dist = sqrtf(distSq);
		result.normal = VScale(diff, 1.0f / dist);
		result.penetration = radiusSum - dist;

		// ★追加：カプセルAの表面とカプセルBの表面のめり込みの中点を接触点とする
		VECTOR pointA = VSub(closestP1, VScale(result.normal, r1));
		VECTOR pointB = VAdd(closestP2, VScale(result.normal, r2));
		result.contactPoint = VScale(VAdd(pointA, pointB), 0.5f);
	}

	return result;
}
// 5. カプセル × ボックス
CollisionResult CollisionLogic::CapsuleToBox(ColliderBase* a, ColliderBase* b)
{
	CollisionResult result;
	auto capsule = dynamic_cast<ColliderCapsule*>(a);
	auto box = dynamic_cast<ColliderBox*>(b);

	bool swapped = false;
	if (!capsule)
	{
		capsule = dynamic_cast<ColliderCapsule*>(b);
		box = dynamic_cast<ColliderBox*>(a);
		swapped = true;
	}
	if (!capsule || !box) return result;

	VECTOR startLocal = box->World2Local(capsule->GetPosDown());
	VECTOR endLocal = box->World2Local(capsule->GetPosTop());
	VECTOR bHalfSize = box->GetHalfSize();
	float capRadius = capsule->GetRadius();

	const int splitCount = 4;
	VECTOR bestClosestLocalP = VGet(0.0f, 0.0f, 0.0f);
	VECTOR bestLocalPos = VGet(0.0f, 0.0f, 0.0f);
	float maxPenetration = -1.0f;
	bool isHit = false;

	for (int i = 0; i <= splitCount; ++i)
	{
		float t = (float)i / (float)splitCount;
		VECTOR currentLocalPos = VAdd(startLocal, VScale(VSub(endLocal, startLocal), t));

		VECTOR closestP;
		closestP.x = fmaxf(-bHalfSize.x, fminf(currentLocalPos.x, bHalfSize.x));
		closestP.y = fmaxf(-bHalfSize.y, fminf(currentLocalPos.y, bHalfSize.y));
		closestP.z = fmaxf(-bHalfSize.z, fminf(currentLocalPos.z, bHalfSize.z));

		VECTOR diffLocal = VSub(currentLocalPos, closestP);
		float distSq = diffLocal.x * diffLocal.x + diffLocal.y * diffLocal.y + diffLocal.z * diffLocal.z;

		if (distSq <= capRadius * capRadius)
		{
			float dist = sqrtf(distSq);
			float penetration = capRadius - dist;

			if (penetration > maxPenetration)
			{
				maxPenetration = penetration;
				bestClosestLocalP = closestP;
				bestLocalPos = currentLocalPos;
				isHit = true;
			}
		}
	}

	if (!isHit) return result;

	result.isHit = true;
	VECTOR finalNormal;
	VECTOR worldPointOnBox = box->Local2World(bestClosestLocalP); // スコープ外に定義

	if (maxPenetration > capRadius - 0.0001f)
	{
		finalNormal = box->GetAxisY();
		result.penetration = capRadius;
		// 深くめり込んでいる場合は、判定に使用したカプセルのセグメント点
		result.contactPoint = box->Local2World(bestLocalPos);
	}
	else
	{
		VECTOR worldPointOnCapsule = box->Local2World(bestLocalPos);
		VECTOR worldDiff = VSub(worldPointOnCapsule, worldPointOnBox);

		float dist = capRadius - maxPenetration;
		finalNormal = VScale(worldDiff, 1.0f / dist);
		result.penetration = maxPenetration;

		// ★追加：ボックス上で最もカプセルに近い点を接触点とする
		result.contactPoint = worldPointOnBox;
	}

	result.normal = swapped ? VScale(finalNormal, -1.0f) : finalNormal;
	return result;
}

CollisionResult CollisionLogic::BoxToBox(ColliderBase* a, ColliderBase* b)
{
	CollisionResult result;
	auto boxA = dynamic_cast<ColliderBox*>(a);
	auto boxB = dynamic_cast<ColliderBox*>(b);
	if (!boxA || !boxB) return result;

	// --- 各種パラメータ取得 ---
	VECTOR centerA = boxA->GetRotPos(boxA->GetColliderInfo().localPos_);
	VECTOR sizeA = boxA->GetHalfSize();
	VECTOR axesA[3] = { boxA->GetAxisX(), boxA->GetAxisY(), boxA->GetAxisZ() };

	VECTOR centerB = boxB->GetRotPos(boxB->GetColliderInfo().localPos_);
	VECTOR sizeB = boxB->GetHalfSize();
	VECTOR axesB[3] = { boxB->GetAxisX(), boxB->GetAxisY(), boxB->GetAxisZ() };

	VECTOR T = VSub(centerB, centerA);

	// --- SAT: 分離軸判定 ---
	VECTOR testAxes[15];
	for (int i = 0; i < 3; ++i) { testAxes[i] = axesA[i]; testAxes[i + 3] = axesB[i]; }
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			testAxes[6 + i * 3 + j] = VCross(axesA[i], axesB[j]);
		}
	}

	float minPenetration = FLT_MAX;
	VECTOR minAxis = VGet(0, 0, 0);

	for (int i = 0; i < 15; ++i) {
		VECTOR axis = testAxes[i];
		if (VDot(axis, axis) < 0.00001f) continue;
		axis = VNorm(axis);

		float rA = sizeA.x * fabsf(VDot(axis, axesA[0])) +
			sizeA.y * fabsf(VDot(axis, axesA[1])) +
			sizeA.z * fabsf(VDot(axis, axesA[2]));
		float rB = sizeB.x * fabsf(VDot(axis, axesB[0])) +
			sizeB.y * fabsf(VDot(axis, axesB[1])) +
			sizeB.z * fabsf(VDot(axis, axesB[2]));

		float dist = fabsf(VDot(T, axis));
		if (dist > rA + rB) return result; // 分離軸発見

		float penetration = (rA + rB) - dist;
		if (penetration < minPenetration) {
			minPenetration = penetration;
			minAxis = axis;
		}
	}

	// --- 衝突確定 ---
	result.isHit = true;
	result.penetration = minPenetration;
	if (VDot(minAxis, T) < 0) minAxis = VScale(minAxis, -1.0f);
	minAxis=VScale(minAxis,-1);
	result.normal = minAxis;

	// --- 高精度な接触点算出（貫通頂点の平均） ---
	VECTOR contactPoint = VGet(0, 0, 0);
	int count = 0;

	auto CalculateContact = [&](ColliderBox* box, VECTOR otherCenter, VECTOR normal) {
		for (int i = 0; i < 8; ++i) {
			VECTOR v = box->GetVertexPos(i);
			// 面の反対側にどれだけ深く入り込んでいるか（簡易判定）
			float dist = VDot(VSub(v, otherCenter), normal);
			if (dist > -0.1f) { // 面付近にある頂点を抽出
				contactPoint = VAdd(contactPoint, v);
				count++;
			}
		}
		};

	CalculateContact(boxA, centerB, minAxis);
	CalculateContact(boxB, centerA, VScale(minAxis, -1.0f));

	if (count > 0) {
		result.contactPoint = VScale(contactPoint, 1.0f / (float)count);
	}
	else {
		result.contactPoint = VScale(VAdd(centerA, centerB), 0.5f);
	}

	return result;
}
// 7. 各種モデル衝突（現在は未実装、空の構造体を返す）
CollisionResult CollisionLogic::SphereToModel(ColliderBase* a, ColliderBase* b) { return CollisionResult(); }
CollisionResult CollisionLogic::CapsuleToModel(ColliderBase* a, ColliderBase* b) { return CollisionResult(); }
CollisionResult CollisionLogic::BoxToModel(ColliderBase* a, ColliderBase* b) { return CollisionResult(); }
CollisionResult CollisionLogic::ModelToModel(ColliderBase* a, ColliderBase* b) { return CollisionResult(); }