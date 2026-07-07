#pragma once
#include "../../ActorBase.h"
class StationBase :
    public ActorBase
{
public:

	StationBase(void);
	~StationBase(void);

	void SubLoad(void) override;
	void SubInit(void) override;
	void SubUpdate(void) override;
	void SubDraw(void) override;
	void SubRelease(void) override;
	void InitCollider(void)override;

private:


};

