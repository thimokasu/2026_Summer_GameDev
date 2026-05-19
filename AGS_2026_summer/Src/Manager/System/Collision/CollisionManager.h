#pragma once
#include<DxLib.h>
#include<memory>
#include<cstdint>
#include<functional>
#include<map>

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

	//è’ìÀâÒêîÇÃè„å¿
	static constexpr int MAX_COLLISION = 3;
	//ÇﬂÇËçûÇ›ÇÃãñóeíl
	static constexpr float PENETRATION_ALLOWANCE = 0.05f;

	CollisionManager(void);
	~CollisionManager(void);

	void AddCollider(ColliderBase* collider,int entityID);
	void RemoveCollider(ColliderBase* collider);
	void ClearColliders(void);

	void Update(void);
	void Resolve(void);

	void SetContactCallbacks(ContactCallback onBegin, ContactCallback onEnd)
	{
		onBegin_ = onBegin;
		onEnd_ = onEnd;
	}

private:
#pragma region ä÷êî

	void DiffPairs
	(
		CollisionPairs& currentPairs, CollisionPairs& prevPairs,
		CollisionPairs& beginPairs, CollisionPairs& endPairs
	);
#pragma endregion

#pragma region ïœêî
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

