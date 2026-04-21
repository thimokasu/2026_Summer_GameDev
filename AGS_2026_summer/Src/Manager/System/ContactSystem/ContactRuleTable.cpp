#include "ContactRuleTable.h"


//ÚG•¨‘Ì‚ÌID‚É‚æ‚éƒCƒxƒ“ƒgí—Ş”»•Ê
ContactRule ContactRuleTable::Query(ContactRule rule)
{

    if (rule.contactEvent_.entityA.entityKind == EntityKind::REACTION_BLOCK && rule.contactEvent_.entityB.entityKind == EntityKind::PLAYER)
    {
        rule.eventType_ = GameEventType::TEST;
    }

    return rule;
}
