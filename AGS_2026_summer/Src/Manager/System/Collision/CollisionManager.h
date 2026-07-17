#pragma once
#include<DxLib.h>
#include<memory>
#include<cstdint>
#include<functional>
#include<map>
#include"CollisionResult.h"
#include"../../../Object/Common/RigidBody.h"
#include"../../../Object/Common/Transform.h"

class ActorBase;
class ColliderBase;

using ContactCallback = std::function<void(std::uint32_t, std::uint32_t)>;
using CollisionPairs = std::vector<std::pair<std::size_t, std::size_t>>;

class CollisionManager
{
public:
	struct CollisionResolve
	{
		ActorBase* actorA;
		ActorBase* actorB;
		CollisionResult result;
	};

	//衝突回数の上限
	static constexpr int MAX_COLLISION = 3;
	//めり込みの許容値
	static constexpr float PENETRATION_ALLOWANCE = 0.05f;

	CollisionManager(void);
	~CollisionManager(void);

	/// <summary>
	/// コライダーの登録
	/// </summary>
	/// <param name="collider"></param>
	/// <param name="entityID"></param>
	void AddCollider(ColliderBase* collider,int entityID);
	/// <summary>
	/// 特定のコライダーを削除
	/// </summary>
	/// <param name="collider"></param>
	void RemoveCollider(ColliderBase* collider);
	/// <summary>
	/// 登録されている全てのコライダーをクリア
	/// </summary>
	void ClearColliders(void);

	/// <summary>
	/// 接触判定を行い、接触しているペアを記録する
	/// </summary>
	/// <param name=""></param>
	void Update(void);

	/// <summary>
	/// 押し出し解決を行う
	/// </summary>
	/// <param name=""></param>
	void Resolve(void);

	/// <summary>
	/// 接触イベントのコールバック関数を設定
	/// </summary>
	/// <param name="onBegin">接触が開始したときに呼び出されるコールバック関数。</param>
	/// <param name="onEnd">接触が終了したときに呼び出されるコールバック関数。</param>
	void SetContactCallbacks(ContactCallback onBegin, ContactCallback onEnd)
	{
		onBegin_ = onBegin;
		onEnd_ = onEnd;
	}
	void DebugDraw(void);
private:
#pragma region 関数

	void DiffPairs
	(
		CollisionPairs& currentPairs, CollisionPairs& prevPairs,
		CollisionPairs& beginPairs, CollisionPairs& endPairs
	);

	void ApplyBodyTorque(RigidBody& rb, Transform& trans, const VECTOR& r, const VECTOR& collisionForce, const VECTOR& normal, float sign);
	void CancelLinearVelocity(RigidBody& rb, const VECTOR& normal, float sign);
	void ApplyCollisionForces(CollisionResolve resolve, float totalInvMass);
	void PositionIntegration(CollisionResolve resolve, float totalInvMass);
#pragma endregion

#pragma region 変数
	std::vector<VECTOR>debugContactPoint_;

	CollisionPairs prevPairs_;

	ContactCallback onBegin_;
	ContactCallback onEnd_;

	struct CollisionObject
	{
		ColliderBase* collider_;
		std::uint32_t entityID_;
	};
	std::vector<CollisionObject>colliders_;
	std::vector<CollisionResolve>resolve_;
#pragma endregion
};

