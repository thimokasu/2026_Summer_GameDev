#pragma once
#include"../MarbleRacePlayer.h"
#include "../../../StateBehavior.h"
class MarbleRaceMove :
    public StateBehavior<MarbleRacePlayer>
{
    void EnterT(MarbleRacePlayer* owner) override;
    void HandleInputT(MarbleRacePlayer* owner) override;
    void UpdateT(MarbleRacePlayer* owner) override;
    void ExitT(MarbleRacePlayer* owner) override;
private:
    VECTOR moveVec_;
};

