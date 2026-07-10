#pragma once
#include "../../StateBehavior.h"
#include "../SwordFightPlayer.h"
class SwordFIght_Walk :
    public StateBehavior<SwordFightPlayer>
{
    void EnterT(SwordFightPlayer* owner) override;
    void HandleInputT(SwordFightPlayer* owner) override;
    void UpdateT(SwordFightPlayer* owner) override;
    void ExitT(SwordFightPlayer* owner) override;
public:
    VECTOR moveVec_ = { 0.0f,0.0f,0.0f };

};
