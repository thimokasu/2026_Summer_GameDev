#pragma once
#include "../../CharactorBase.h"
class MarbleRacePlayer :
    public CharactorBase
{
public:
    MarbleRacePlayer(void);
    ~MarbleRacePlayer(void);

    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;

private:
    void InitRigidBody(void)override;
    void InitCollider(void) override;
    void ReturnToIdle(void)override;
    void CreateState(void) override;
};

