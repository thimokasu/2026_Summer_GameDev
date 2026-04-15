#include "ContactSystem.h"

void ContactSystem::OnBeginContact(Entity a, Entity b, CollisionResult result)
{
	touching_[a.entityId].insert(b.entityId);
	touching_[b.entityId].insert(a.entityId);

	contactRules_.push_back(
		ContactRule{
			ContactEventInfo{
				ContactEventInfo::Type::BEGIN,
				a,
				b
			}
		});
}

void ContactSystem::OnEndContact(Entity a, Entity b, CollisionResult result)
{
	touching_[a.entityId].erase(b.entityId);
	touching_[b.entityId].erase(a.entityId);

	contactRules_.push_back(
		ContactRule{
			ContactEventInfo{
				ContactEventInfo::Type::END,
				a,
				b
			}
		});

}

