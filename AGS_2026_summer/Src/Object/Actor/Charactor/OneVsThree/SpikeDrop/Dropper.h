#pragma once
#include "../../CharactorBase.h"
class Dropper :
    public CharactorBase
{
public:
    Dropper(void);
    ~Dropper(void);

    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;

private:
    void InitCollider(void) override;
    void InitRigidBody(void)override;
    void ReturnToIdle(void)override;
    void CreateState(void)override;

};

