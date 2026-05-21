#pragma once
#include<map>
#include<set>
#include<unordered_map>
#include<functional>
#include<utility>
#include"../Collision/CollisionResult.h"
#include"ContactEventInfo.h"

class ContactEventManager
{
public:
	std::unordered_map<GameEventType, std::vector<std::function<void(const ContactRule&)>>> collbackEevnt_;
	ContactEventManager(void);
	~ContactEventManager(void);

	void OnBeginContact(Entity a, Entity b, CollisionResult result);
	void OnEndContact(Entity a, Entity b, CollisionResult result);

	void Update(void);

	void Clear(void) { contactRules_.clear(); touching_.clear(); }


	void SetContactEventCallback(GameEventType eventType, std::function<void()> callback);
	/// <summary>
	/// 発生させるイベントのコールバック関数を登録する
	/// </summary>
	/// <param name="eventType">イベントの種類</param>
	/// <param name="callback">コールバック関数</param>
	/// <param name="const ContactRule&">コールバックで呼び出される関数に渡すための引数</param>
	void SetContactEventCallback(GameEventType eventType, std::function<void(const ContactRule&)> callback)
	{
		collbackEevnt_[eventType].push_back(callback);
	}

	/// <summary>
	/// 発生させるイベントのルールを設定する
	/// </summary>
	/// <param name="kindA">オブジェクトの種類A</param>
	/// <param name="kindB">オブジェクトの種類B</param>
	/// <param name="eventType">発生させるイベントの種類</param>
	void SetEventRule(EntityKind kindA, EntityKind kindB, GameEventType eventType);

private:
	ContactRule Query(ContactRule rule);
	std::map<EntityID, std::set<EntityID>> touching_;
	std::vector<ContactRule> contactRules_;

	std::map<std::pair<EntityKind, EntityKind>, GameEventType> ruleTable_;
};

