#pragma once
#include "../CharactorBase.h"
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

};

