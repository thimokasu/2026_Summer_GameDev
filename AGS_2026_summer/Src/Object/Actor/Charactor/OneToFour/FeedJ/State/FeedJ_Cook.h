#pragma once
#include "../../../StateBehavior.h"
#include "../FeedJPlayer.h"
class FeedJ_Cook :
    public StateBehavior<FeedJPlayer>
{
public:
    void EnterT(FeedJPlayer* owner) override;
    void HandleInputT(FeedJPlayer* owner) override;
    void UpdateT(FeedJPlayer* owner) override;
    void ExitT(FeedJPlayer* owner) override;
};


