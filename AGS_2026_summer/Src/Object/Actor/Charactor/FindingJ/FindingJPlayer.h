#pragma once
#include "../CharactorBase.h"
class FindingJPlayer :
    public CharactorBase
{
    public:
        FindingJPlayer(void);
    virtual ~FindingJPlayer(void);
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
	void InitCollider(void) override;

private:
	void MoveInput(void) override;
};
