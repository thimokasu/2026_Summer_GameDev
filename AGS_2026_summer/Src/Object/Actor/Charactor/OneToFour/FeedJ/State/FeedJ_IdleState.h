#pragma once
#include "../../../IState.h"
#include "../../../StateBehavior.h"
#include "../FeedJPlayer.h"

class FeedJ_IdleState :
    public StateBehavior<FeedJPlayer>
{
public:
    //CharactorBaseにない処理を実装したい場合はIStateではなく
    //StateBehaviorを継承し
    //テンプレートを使用して実装する
    void EnterT(FeedJPlayer* owner) override;
    void HandleInputT(FeedJPlayer* owner) override;
    void UpdateT(FeedJPlayer* owner) override;
    void ExitT(FeedJPlayer* owner) override;
};

