#include "CollisionLogic.h"
#include <type_traits>  
#include <algorithm>  
#include"../../../Object/Actor/Collider/ColliderInfo.h"
#include"../../../Object/Actor/Collider/ColliderBase.h"

#include"../../../Object/Actor/Collider/ColliderSphere.h"
#include"../../../Object/Actor/Collider/ColliderBox.h"
#include"../../../Object/Actor/Collider/ColliderCapsule.h"
CollisionLogic::CollisionLogic(void)
{
}

CollisionLogic::~CollisionLogic(void)
{
}

CollisionPairType CollisionLogic::GetCollisionPairType(SHAPE shapeA, SHAPE shapeB)
{
    // 同じ形状同士  
    if (shapeA == shapeB)
    {
        switch (shapeA)
        {
        case SHAPE::SPHERE:   return CollisionPairType::SPHERE_SPHERE;
        case SHAPE::CAPSULE: return CollisionPairType::CAPSULE_CAPSULE;
        case SHAPE::BOX:     return CollisionPairType::BOX_BOX;
        default:             return CollisionPairType::NONE;
        }
    }

    // 順序を吸収（小さいほうをAに）  
    if (shapeA > shapeB)
        std::swap(shapeA, shapeB);

    // 異なる形状同士  
    if (shapeA == SHAPE::SPHERE && shapeB == SHAPE::CAPSULE)
        return CollisionPairType::SPHERE_CAPSULE;

    if (shapeA == SHAPE::SPHERE && shapeB == SHAPE::BOX)
        return CollisionPairType::SPHERE_BOX;

    if (shapeA == SHAPE::CAPSULE && shapeB == SHAPE::BOX)
        return CollisionPairType::CAPSULE_BOX;

    if (shapeA == SHAPE::SPHERE && shapeB == SHAPE::MODEL)
        return CollisionPairType::SPHERE_MODEL;

    if (shapeA == SHAPE::CAPSULE && shapeB == SHAPE::MODEL)
        return CollisionPairType::CAPSULE_MODEL;

    if (shapeA == SHAPE::BOX && shapeB == SHAPE::MODEL)
        return CollisionPairType::BOX_MODEL;

    if (shapeA == SHAPE::MODEL && shapeB == SHAPE::MODEL)
        return CollisionPairType::MODEL_MODEL;

    return CollisionPairType::NONE;
}

CollisionResult CollisionLogic::DispatchCollision(CollisionPairType pairType, 
    const std::shared_ptr<ColliderBase>& a,
    const std::shared_ptr<ColliderBase>& b)
{
    CollisionResult result;
    switch (pairType)
    {
    case CollisionPairType::NONE:
        break;
    case CollisionPairType::SPHERE_SPHERE:
        result = SphereToSphere(a, b);
        break;
    case CollisionPairType::SPHERE_CAPSULE:
        result = SphereToCapsule(a, b);
        break;
    case CollisionPairType::SPHERE_BOX:
        result = SphereToBox(a, b);
        break;
    case CollisionPairType::CAPSULE_CAPSULE:
        result = CapsuleToCapsule(a, b);
        break;
    case CollisionPairType::CAPSULE_BOX:
        result = CapsuleToBox(a, b);
        break;
    case CollisionPairType::BOX_BOX:
        result = BoxToBox(a, b);
        break;
    case CollisionPairType::SPHERE_MODEL:
        result = SphereToModel(a, b);
        break;
    case CollisionPairType::CAPSULE_MODEL:
        result = CapsuleToModel(a, b);
        break;
    case CollisionPairType::BOX_MODEL:
        result = BoxToModel(a, b);
        break;
    case CollisionPairType::MODEL_MODEL:
        result = ModelToModel(a, b);
        break;
    default:
        break;
    }

    return result;
}

CollisionResult CollisionLogic::SphereToSphere(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    CollisionResult result;
    //キャスト
    auto sphereA = std::dynamic_pointer_cast<ColliderSphere>(a);
    auto sphereB = std::dynamic_pointer_cast<ColliderSphere>(b);
    //キャスト失敗
    if (!sphereA || !sphereB) return result;
	//中心点と半径の和を求める
    VECTOR posA = sphereA->GetFollow()->pos;
    VECTOR posB = sphereB->GetFollow()->pos;
    float radiusSum = sphereA->GetRadius() + sphereB->GetRadius();
	//BからAへのベクトルを求める
    VECTOR diff = VSub(posA, posB);
	//距離の二乗を求める
    float distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	//距離の二乗が半径の和の二乗より大きい場合は衝突していない
    if (distSq > radiusSum * radiusSum) return result;
	//衝突している
    result.isHit = true;
	//距離が非常に近い場合は、正規化できないので特例で上向きの法線を返す
    if (distSq < 0.0001f) {
        result.normal = VGet(0.0f, 1.0f, 0.0f);
        result.penetration = radiusSum;
    }
	//BからAへの正規化ベクトルを法線として返す
    else {
        float dist = sqrtf(distSq);
        result.normal = VScale(diff, 1.0f / dist); 
        result.penetration = radiusSum - dist;
    }
    return result;
}

CollisionResult CollisionLogic::SphereToCapsule(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    CollisionResult result;
    //キャスト
    auto sphere = std::dynamic_pointer_cast<ColliderSphere>(a);
    auto capsule = std::dynamic_pointer_cast<ColliderCapsule>(b);
	//入れ替え吸収
    bool swapped = false;
	//もしAが球でなければ入れ替える
    if (!sphere) {
        sphere = std::dynamic_pointer_cast<ColliderSphere>(b);
        capsule = std::dynamic_pointer_cast<ColliderCapsule>(a);
        swapped = true;
    }
	//キャスト失敗
    if (!sphere || !capsule) return result;
	//球中心点とカプセルの両端点を取得
    VECTOR sPos = sphere->GetFollow()->pos;
    VECTOR capA = capsule->GetPosDown();
    VECTOR capB = capsule->GetPosTop();

    // 線分上の最短地点を計算
    VECTOR ab = VSub(capB, capA);
    VECTOR ap = VSub(sPos, capA);
    float l2 = VDot(ab, ab);
    float t = (l2 > 0.0f) ? VDot(ap, ab) / l2 : 0.0f;
    t = fmaxf(0.0f, fminf(1.0f, t));
    VECTOR nearestP = VAdd(capA, VScale(ab, t));

    VECTOR diff = VSub(sPos, nearestP);
	//距離の二乗を求める
    float distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	//半径の和を求める
    float radiusSum = sphere->GetRadius() + capsule->GetRadius();
	//距離の二乗が半径の和の二乗より大きい場合は衝突していない
    if (distSq > radiusSum * radiusSum) return result;
	//衝突している
    result.isHit = true;
    VECTOR finalNormal;
	//距離が非常に近い場合は、正規化できないので特例で上向きの法線を返す
    if (distSq < 0.0001f) {
        finalNormal = VGet(0, 1, 0);
        result.penetration = radiusSum;
    }
	//BからAへの正規化ベクトルを法線として返す
    else {
        float dist = sqrtf(distSq);
        finalNormal = VScale(diff, 1.0f / dist);
        result.penetration = radiusSum - dist;
    }

	// 入れ替わっていたら反転
    result.normal = swapped ? VScale(finalNormal, -1.0f) : finalNormal;

    return result;
}

CollisionResult CollisionLogic::SphereToBox(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    CollisionResult result;
    //キャスト
    auto sphere = std::dynamic_pointer_cast<ColliderSphere>(a);
    auto box = std::dynamic_pointer_cast<ColliderBox>(b);
	//入れ替え吸収
    bool swapped = false;
    if (!sphere) {
        sphere = std::dynamic_pointer_cast<ColliderSphere>(b);
        box = std::dynamic_pointer_cast<ColliderBox>(a);
        swapped = true;
    }
    if (!sphere || !box) return result;
	// 球中心点のワールド座標をボックスのローカル座標に変換
    VECTOR sWorldPos = sphere->GetFollow()->pos;
    VECTOR sLocalPos = box->World2Local(sWorldPos);
    VECTOR bHalfSize = box->GetHalfSize();

    // ボックス内の最短地点をクランプで求める
    VECTOR closestLocalP;
    closestLocalP.x = fmaxf(-bHalfSize.x, fminf(sLocalPos.x, bHalfSize.x));
    closestLocalP.y = fmaxf(-bHalfSize.y, fminf(sLocalPos.y, bHalfSize.y));
    closestLocalP.z = fmaxf(-bHalfSize.z, fminf(sLocalPos.z, bHalfSize.z));
	// 球中心点と最短地点の差分ベクトルを求める
    VECTOR diffLocal = VSub(sLocalPos, closestLocalP);
    float distSq = diffLocal.x * diffLocal.x + diffLocal.y * diffLocal.y + diffLocal.z * diffLocal.z;
    float sRadius = sphere->GetRadius();
	//距離の二乗が半径の二乗より大きい場合は衝突していない
    if (distSq > sRadius * sRadius) return result;

    result.isHit = true;
    VECTOR finalNormal;
	//距離が非常に近い場合は、正規化できないので特例で上向きの法線を返す
    if (distSq < 0.0001f) {
        finalNormal = box->GetAxisY();
        result.penetration = sRadius;
    }
	//BからAへの正規化ベクトルを法線として返す
    else {
        float dist = sqrtf(distSq);
        VECTOR worldPointOnBox = box->Local2World(closestLocalP);
        finalNormal = VScale(VSub(sWorldPos, worldPointOnBox), 1.0f / dist);

        result.penetration = sRadius - dist;
    }

	// 入れ替わっていたら反転
    result.normal = swapped ? VScale(finalNormal, -1.0f) : finalNormal;
    return result;
}

CollisionResult CollisionLogic::CapsuleToCapsule(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    CollisionResult result;
    //キャスト
    auto capA = std::dynamic_pointer_cast<ColliderCapsule>(a);
    auto capB = std::dynamic_pointer_cast<ColliderCapsule>(b);

    if (!capA || !capB) return result;
	//カプセルAの両端点と半径を取得
    VECTOR p1 = capA->GetPosDown();
    VECTOR q1 = capA->GetPosTop();
    float r1 = capA->GetRadius();
	//カプセルBの両端点と半径を取得
    VECTOR p2 = capB->GetPosDown();
    VECTOR q2 = capB->GetPosTop();
    float r2 = capB->GetRadius();

	//線分間の最短距離を求める
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
	//denが0の場合は線分が平行なので、sを0に固定してtを求める
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

    // 各線分上の最短地点
    VECTOR closestP1 = VAdd(p1, VScale(d1, s));
    VECTOR closestP2 = VAdd(p2, VScale(d2, t));

	// 最短地点同士の差分ベクトル
    VECTOR diff = VSub(closestP1, closestP2);

    float distSq = VDot(diff, diff);
    float radiusSum = r1 + r2;

    if (distSq > radiusSum * radiusSum) return result;

    //
    result.isHit = true;
    if (distSq < 0.0001f) {
        result.normal = VGet(0, 1, 0);
        result.penetration = radiusSum;
    }
    else {
        float dist = sqrtf(distSq);
        result.normal = VScale(diff, 1.0f / dist);
        result.penetration = radiusSum - dist;
    }

    return result;
}

CollisionResult CollisionLogic::CapsuleToBox(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    CollisionResult result;

    auto capsule = std::dynamic_pointer_cast<ColliderCapsule>(a);
    auto box = std::dynamic_pointer_cast<ColliderBox>(b);

    //順序が逆の場合の処理
    bool swapped = false;
    if (!capsule)
    {
        capsule = std::dynamic_pointer_cast<ColliderCapsule>(b);
        box = std::dynamic_pointer_cast<ColliderBox>(a);
        swapped = true;
    }

    if (!capsule || !box) return result;

    // --- 1. 座標系の変換 ---
    VECTOR startLocal = box->World2Local(capsule->GetPosDown());
    VECTOR endLocal = box->World2Local(capsule->GetPosTop());
    VECTOR bHalfSize = box->GetHalfSize();
    float capRadius = capsule->GetRadius();

    // --- 2. 線分を分割して各点でチェック ---
    const int splitCount = 4;
    VECTOR bestClosestLocalP = VGet(0, 0, 0);
    VECTOR bestLocalPos = VGet(0, 0, 0);
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

    // --- 3. 結果の構築 ---
    result.isHit = true;
    VECTOR finalNormal;

    if (maxPenetration > capRadius - 0.0001f)
    {
        finalNormal = box->GetAxisY();
        result.penetration = capRadius;
    }
    else
    {
        VECTOR worldPointOnCapsule = box->Local2World(bestLocalPos);
        VECTOR worldPointOnBox = box->Local2World(bestClosestLocalP);

        VECTOR worldDiff = VSub(worldPointOnCapsule, worldPointOnBox);

        float dist = capRadius - maxPenetration;
        finalNormal = VScale(worldDiff, 1.0f / dist);
        result.penetration = maxPenetration;
    }

    // wappedなら反転
    result.normal = swapped ? VScale(finalNormal, -1.0f) : finalNormal;

    return result;
}

CollisionResult CollisionLogic::BoxToBox(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    CollisionResult result;
    auto boxA = std::dynamic_pointer_cast<ColliderBox>(a);
    auto boxB = std::dynamic_pointer_cast<ColliderBox>(b);
    if (!boxA || !boxB) return result;

    // 1. 各ボックスの情報を整理
    VECTOR posA = boxA->GetFollow()->pos;
    VECTOR posB = boxB->GetFollow()->pos;
    VECTOR axisA[3] = { boxA->GetAxisX(), boxA->GetAxisY(), boxA->GetAxisZ() };
    VECTOR axisB[3] = { boxB->GetAxisX(), boxB->GetAxisY(), boxB->GetAxisZ() };
    VECTOR hA = boxA->GetHalfSize();
    VECTOR hB = boxB->GetHalfSize();

    VECTOR L = VSub(posA, posB);

    float minOverlap = 1e10f;
    VECTOR bestAxis = VGet(0, 0, 0);

    // 2. 15本の分離軸候補
    VECTOR testAxes[15];
    for (int i = 0; i < 3; ++i) testAxes[i] = axisA[i];
    for (int i = 0; i < 3; ++i) testAxes[i + 3] = axisB[i];

    int axisIdx = 6;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            testAxes[axisIdx++] = VCross(axisA[i], axisB[j]);
        }
    }

    // --- 3. 各軸において重なりを計算 ---
    for (int i = 0; i < 15; ++i) {
        VECTOR axis = testAxes[i];
        float axisLenSq = VDot(axis, axis);
        if (axisLenSq < 0.0001f) continue;

        axis = VScale(axis, 1.0f / sqrtf(axisLenSq));

        float rA = hA.x * fabsf(VDot(axisA[0], axis)) + hA.y * fabsf(VDot(axisA[1], axis)) + hA.z * fabsf(VDot(axisA[2], axis));
        float rB = hB.x * fabsf(VDot(axisB[0], axis)) + hB.y * fabsf(VDot(axisB[1], axis)) + hB.z * fabsf(VDot(axisB[2], axis));

        float dist = fabsf(VDot(L, axis));
        float overlap = (rA + rB) - dist;

        if (overlap <= 0.0f) return result;

        if (i >= 6) overlap *= 0.95f; // 辺同士より面同士を優先

        if (overlap < minOverlap) {
            minOverlap = overlap;
            bestAxis = axis;
        }
    }

    // 4. 法線の向きを補正
    if (VDot(L, bestAxis) < 0)
    {
        bestAxis = VScale(bestAxis, -1.0f);
    }

    result.isHit = true;
    result.penetration = minOverlap;
    result.normal = bestAxis; // これで normal は常に B -> A 方向

    return result;
}

CollisionResult CollisionLogic::SphereToModel(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    return CollisionResult();
}

CollisionResult CollisionLogic::CapsuleToModel(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    return CollisionResult();
}

CollisionResult CollisionLogic::BoxToModel(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    return CollisionResult();
}

CollisionResult CollisionLogic::ModelToModel(const std::shared_ptr<ColliderBase>& a, const std::shared_ptr<ColliderBase>& b)
{
    return CollisionResult();
}
