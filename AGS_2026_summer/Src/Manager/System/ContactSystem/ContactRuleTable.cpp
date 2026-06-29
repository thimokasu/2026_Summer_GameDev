#include "ContactRuleTable.h"


//ê⁄êGï®ëÃÇÃIDÇ…ÇÊÇÈÉCÉxÉìÉgéÌóﬁîªï 
ContactRule ContactRuleTable::Query(ContactRule rule)
{

    if (rule.contactEvent_.entityA.entityKind == EntityKind::REACTION_BLOCK && rule.contactEvent_.entityB.entityKind == EntityKind::RUNNER)
    {
        rule.eventType_ = GameEventType::REACTION_BLOCK;
    }
    if (rule.contactEvent_.entityA.entityKind == EntityKind::RUNNER && rule.contactEvent_.entityB.entityKind == EntityKind::REACTION_BLOCK)
    {
        rule.eventType_ = GameEventType::REACTION_BLOCK;
    }
    if(rule.contactEvent_.entityA.entityKind == EntityKind::CHASER && rule.contactEvent_.entityB.entityKind == EntityKind::RUNNER)
    {
        rule.eventType_ = GameEventType::HAS_CAUGHT;
	}

    return rule;
}
