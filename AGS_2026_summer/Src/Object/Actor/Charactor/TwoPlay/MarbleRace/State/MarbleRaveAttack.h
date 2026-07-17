#pragma once
#include "../../../StateBehavior.h"
#include"../MarbleRacePlayer.h"
class MarbleRaveAttack :
    public StateBehavior<MarbleRacePlayer>
{
    void EnterT(MarbleRacePlayer* owner) override;
    void HandleInputT(MarbleRacePlayer* owner) override;
    void UpdateT(MarbleRacePlayer* owner) override;
    void ExitT(MarbleRacePlayer* owner) override;

private:
    VECTOR moveVec_;

};

