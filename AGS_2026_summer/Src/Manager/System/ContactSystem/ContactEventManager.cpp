#include "ContactEventManager.h"

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
	for (auto rule : contactRules_)
	{
		auto event = contactEventTable_.Query(rule);
		auto it = collbackEevnt_.find(event.eventType_);
		if (it != collbackEevnt_.end())
		{
			it->second(rule);
		}
	}
	Clear();
}
