#pragma once
#include"../MarbleRacePlayer.h"
#include "../../../StateBehavior.h"
class MarbleRaceIdle :
    public StateBehavior<MarbleRacePlayer>
{
    void EnterT(MarbleRacePlayer* owner) override;
    void HandleInputT(MarbleRacePlayer* owner) override;
    void UpdateT(MarbleRacePlayer* owner) override;
    void ExitT(MarbleRacePlayer* owner) override;

private:
    VECTOR moveVec_;
};

