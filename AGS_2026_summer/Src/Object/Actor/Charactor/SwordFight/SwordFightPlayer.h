#pragma once
#include "../CharactorBase.h"

class SwordFightPlayer :
    public CharactorBase
{
public:
    SwordFightPlayer(void);
    virtual ~SwordFightPlayer(void);
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
    void InitCollider(void) override;

private:
    void MoveInput(void) override;
};
