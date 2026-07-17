#pragma once
#include "../../CharactorBase.h"
class SpikeDropPlayer :
    public CharactorBase
{
public:
    SpikeDropPlayer(void);
    ~SpikeDropPlayer(void);

    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
    void InitCollider(void) override;
    void InitRigidBody(void)override;

private:
    void ReturnToIdle(void)override;
    void CreateState(void)override;

};

