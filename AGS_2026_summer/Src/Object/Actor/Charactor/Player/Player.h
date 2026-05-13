#pragma once
#include "../CharactorBase.h"
#include "../../../../Net/NetStructures.h"
#include"NetPlayerID.h"
class Player :
    public CharactorBase
{
    public:
    Player(void);
    virtual ~Player(void);
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
private:
    void MoveInput(void);
	NetPlayerID netPlayerID_;
};

