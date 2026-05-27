#pragma once
#include "../../CharactorBase.h"
class FindingJ :
    public CharactorBase
{
    public:
    FindingJ(void);
    virtual ~FindingJ(void);
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
	void InitCollider(void) override;

private:
	void MoveInput(void) override;
};
