#pragma once
#include "../../CharactorBase.h"
class AthleticPlayer :
    public CharactorBase
{
public:
    AthleticPlayer(void);
    ~AthleticPlayer(void);

    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
    void InitCollider(void) override;
    void InitRigidBody(void)override;

private:
    void MoveInput(void);
    void JumpInput(void);
};

