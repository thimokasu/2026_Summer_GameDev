#pragma once
#include "../../../StateBehavior.h"
#include "../FeedJPlayer.h"
class FeedJ_HoldState :
    public StateBehavior<FeedJPlayer>
{
    void EnterT(FeedJPlayer* owner) override;
    void HandleInputT(FeedJPlayer* owner) override;
    void UpdateT(FeedJPlayer* owner) override;
    void ExitT(FeedJPlayer* owner) override;
};


