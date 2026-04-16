#include "ContactRuleTable.h"


//ÚG•¨‘Ì‚ÌID‚É‚æ‚éƒCƒxƒ“ƒgí—Ş”»•Ê
ContactRule ContactRuleTable::Query(ContactRule rule)
{

    if (rule.contactEvent_.entityA.entityKind == EntityKind::STAGE && rule.contactEvent_.entityB.entityKind == EntityKind::STAGE)
    {
        rule.eventType_ = GameEventType::TEST;
    }

    return rule;
}
