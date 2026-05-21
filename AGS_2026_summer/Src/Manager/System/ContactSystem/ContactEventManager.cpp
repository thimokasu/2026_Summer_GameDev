#include "ContactEventManager.h"
#include<algorithm>
ContactEventManager::ContactEventManager(void)
{
}

ContactEventManager::~ContactEventManager(void)
{
	Clear();
}

void ContactEventManager::OnBeginContact(Entity a, Entity b, CollisionResult result)
{
	touching_[a.entityID_].insert(b.entityID_);
	touching_[b.entityID_].insert(a.entityID_);
	contactRules_.push_back(
		ContactRule{
			ContactEventInfo{
			ContactEventInfo::Type::BEGIN,
			a,b
			}
		}
	);
}

void ContactEventManager::OnEndContact(Entity a, Entity b, CollisionResult result)
{
	touching_[a.entityID_].erase(b.entityID_);
	touching_[b.entityID_].erase(a.entityID_);

	contactRules_.push_back(
		ContactRule{
			ContactEventInfo{
				ContactEventInfo::Type::END,
				a,
				b
			}
		});
}

void ContactEventManager::Update(void)
{
	for (auto& rule : contactRules_)
	{
		auto event =Query(rule);
		auto it = collbackEevnt_.find(event.eventType_);
		if (it != collbackEevnt_.end())
		{
			for (const auto& callback : it->second)
			{
				callback(rule);
			}
		}
	}
	Clear();
}

void ContactEventManager::SetContactEventCallback(GameEventType eventType, std::function<void()> callback)
{
	collbackEevnt_[eventType].push_back([callback](const ContactRule&) { callback(); });
}


void ContactEventManager::SetEventRule(EntityKind kindA, EntityKind kindB, GameEventType eventType)
{
	ruleTable_[std::make_pair(kindA, kindB)] = eventType;
	ruleTable_[std::make_pair(kindB, kindA)] = eventType;
}

ContactRule ContactEventManager::Query(ContactRule rule)
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