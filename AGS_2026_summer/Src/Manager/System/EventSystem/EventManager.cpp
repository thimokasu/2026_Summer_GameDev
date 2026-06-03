#include "EventManager.h"
#include <algorithm>

EventManager* EventManager::instance_ = nullptr;

void EventManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new EventManager();
    }
}

EventManager& EventManager::GetInstance(void)
{
    return *instance_;
}

void EventManager::DeleteInstance(void)
{
    if (instance_ != nullptr)
    {
        delete instance_;
        instance_ = nullptr;
    }
}

// コンストラクタの実体
EventManager::EventManager(void)
{
}

void EventManager::OnBeginContact(Entity a, Entity b, CollisionResult result)
{
    touching_[a.entityID_].insert(b.entityID_);
    touching_[b.entityID_].insert(a.entityID_);

    contactRules_.push_back(
        ContactRule{ ContactEventInfo{ ContactEventInfo::Type::BEGIN, a, b }, GameEventType::NONE }
    );
}

void EventManager::OnEndContact(Entity a, Entity b, CollisionResult result)
{
    // 接触リストから削除
    if (touching_.count(a.entityID_)) touching_[a.entityID_].erase(b.entityID_);
    if (touching_.count(b.entityID_)) touching_[b.entityID_].erase(a.entityID_);

    contactRules_.push_back(
        ContactRule{ ContactEventInfo{ ContactEventInfo::Type::END, a, b }, GameEventType::NONE }
    );
}

void EventManager::Update(void)
{
    isUpdate = true; // ループ開始フラグを立てる

    for (auto& rule : contactRules_)
    {
        auto event = Query(rule);
        auto it = callbackEvent_.find(event.eventType_);
        if (it != callbackEvent_.end())
        {
            // コールバック関数の配列をコピーして回す（ループ内での配列変更対策をさらに強化）
            auto callbacks = it->second;
            for (const auto& callback : callbacks)
            {
                callback(event); // クエリ後の正しい eventType_ が入ったものを渡す
            }
        }
    }

    isUpdate = false; // ループ終了

    // ループ中に保留された新しいコールバックがあれば、ここで安全に追加する
    for (auto& pending : pendingAdds)
    {
        callbackEvent_[pending.first].push_back(pending.second);
    }
    pendingAdds.clear();

    ClearQueue();
}

void EventManager::SetContactEventCallback(GameEventType eventType, std::function<void()> callback)
{
    SetContactEventCallback(eventType, [callback](const ContactRule&) { callback(); });
}

void EventManager::SetContactEventCallback(GameEventType eventType, std::function<void(const ContactRule&)> callback)
{
    if (isUpdate)
    {
        // Update中なら保留リストに入れる
        pendingAdds.push_back({ eventType, callback });
    }
    else
    {
        // 安全な状態なら即時追加
        callbackEvent_[eventType].push_back(callback);
    }
}

void EventManager::SetEventRule(EntityKind kindA, EntityKind kindB, GameEventType eventType)
{
    ruleTable_[std::make_pair(kindA, kindB)] = eventType;
    ruleTable_[std::make_pair(kindB, kindA)] = eventType;
}

void EventManager::TriggerEvent(GameEventType eventType)
{
    auto it = callbackEvent_.find(eventType);
    if (it != callbackEvent_.end())
    {
        auto callbacks = it->second;
        for (const auto& callback : callbacks)
        {
            callback(ContactRule{}); 
        }
	}
}


ContactRule EventManager::Query(ContactRule rule)
{
    auto A = rule.contactEvent_.entityA.entityKind_;
    auto B = rule.contactEvent_.entityB.entityKind_;

    auto it = ruleTable_.find(std::make_pair(A, B));
    if (it != ruleTable_.end())
    {
        rule.eventType_ = it->second;
    }
    else
    {
        rule.eventType_ = GameEventType::NONE;
    }

    return rule;
}