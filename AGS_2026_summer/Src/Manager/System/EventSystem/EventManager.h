#pragma once
#include <map>
#include <set>
#include <unordered_map>
#include <functional>
#include <utility>
#include <vector>
#include "../Collision/CollisionResult.h"
#include "EventInfo.h"

class EventManager
{
public:
    static void CreateInstance(void);
    static EventManager& GetInstance(void);
    static void DeleteInstance(void);
private:
    static EventManager* instance_;
    EventManager(void);
    EventManager(const EventManager& instance) = default;
    ~EventManager(void) = default;
public:

    void OnBeginContact(Entity a, Entity b, CollisionResult result);
    void OnEndContact(Entity a, Entity b, CollisionResult result);

    void Update(void);

    void Clear(void)
    {
        touching_.clear();
        contactRules_.clear();
        ruleTable_.clear();
        callbackEvent_.clear();
    }

    // contactRules_ だけをクリアするように変更
    void ClearQueue(void) { contactRules_.clear(); }
	//シーンごとにイベントルールをリセットするための関数
	void ClearRules(void) { ruleTable_.clear(); }
	//保持しているコールバックをすべてクリアする関数
	void ClearCallbacks(void) { callbackEvent_.clear(); }

    void SetContactEventCallback(GameEventType eventType, std::function<void()> callback);
    void SetContactEventCallback(GameEventType eventType, std::function<void(const ContactRule&)> callback);
    void SetEventRule(EntityKind kindA, EntityKind kindB, GameEventType eventType);
    //外部からイベントを発生
	void TriggerEvent(GameEventType eventType);

private:
    ContactRule Query(ContactRule rule);

    std::map<EntityID, std::set<EntityID>> touching_;
    std::vector<ContactRule> contactRules_;
    std::map<std::pair<EntityKind, EntityKind>, GameEventType> ruleTable_;

    // コールバック関数を一元管理するマップ
    std::unordered_map<GameEventType, std::vector<std::function<void(const ContactRule&)>>> callbackEvent_;

    // --- 処理中の追加に対応するためのバッファ ---
    bool isUpdate = false; // 現在イベント処理中かどうかのフラグ
    std::vector<std::pair<GameEventType, std::function<void(const ContactRule&)>>> pendingAdds;
};