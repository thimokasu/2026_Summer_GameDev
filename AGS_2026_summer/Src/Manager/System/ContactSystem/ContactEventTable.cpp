#include "ContactEventTable.h"

ContactRule ContactEventTable::Query(ContactRule rule)
{
    auto A = rule.contactEvent_.entityA.entityKind_;
    auto B = rule.contactEvent_.entityB.entityKind_;

    // 「AがPLAYER かつ BがSTAGE」 または 「AがSTAGE かつ BがPLAYER」
    if ((A == EntityKind::PLAYER && B == EntityKind::STAGE) ||
        (A == EntityKind::STAGE && B == EntityKind::PLAYER))
    {
        rule.eventType_ = GameEventType::TEST;
    }

    return rule;
}