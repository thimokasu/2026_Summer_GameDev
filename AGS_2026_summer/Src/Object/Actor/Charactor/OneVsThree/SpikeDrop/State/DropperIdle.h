#pragma once
#include"../../../StateBehavior.h"
#include"../Dropper.h"

class DropperIdle :
    public StateBehavior<Dropper>
{
public:
    void EnterT(Dropper* owner) override;
    void HandleInputT(Dropper* owner) override;
    void UpdateT(Dropper* owner) override;
    void ExitT(Dropper* owner) override;
};

