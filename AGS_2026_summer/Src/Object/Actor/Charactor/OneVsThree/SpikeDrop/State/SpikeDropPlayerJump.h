#pragma once
#include "../../../StateBehavior.h"
#include"../SpikeDropPlayer.h"
class SpikeDropPlayerJump :
    public StateBehavior<SpikeDropPlayer>
{
public:
    void EnterT(SpikeDropPlayer* owner) override;
    void HandleInputT(SpikeDropPlayer* owner) override;
    void UpdateT(SpikeDropPlayer* owner) override;
    void ExitT(SpikeDropPlayer* owner) override;
};


