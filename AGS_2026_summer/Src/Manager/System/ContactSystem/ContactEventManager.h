#pragma once
#include<map>
#include<set>
#include<unordered_map>
#include<functional>
#include"../Collision/CollisionResult.h"
#include"ContactEventInfo.h"
#include"ContactEventTable.h"

class ContactEventManager
{
public:
	std::unordered_map<GameEventType, std::function<void(const ContactRule&)>>collbackEevnt_;

	ContactEventManager(void);
	~ContactEventManager(void);

	void OnBeginContact(Entity a, Entity b, CollisionResult result);
	void OnEndContact(Entity a, Entity b, CollisionResult result);

	void Update(void);

	void Clear(void) { contactRules_.clear(); touching_.clear(); }
private:
	std::map<EntityID, std::set<EntityID>> touching_;
	std::vector<ContactRule>contactRules_;
	ContactEventTable contactEventTable_;
};

