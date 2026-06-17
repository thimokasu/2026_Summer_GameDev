#pragma once
#include "../ActorBase.h"
class CharactorBase :
    public ActorBase
{
public:
	CharactorBase(void);
	virtual ~CharactorBase(void);

	void SubLoad(void) override;
	void SubInit(void) override;
	void SubUpdate(void) override;
	void SubDraw(void) override;
	void SubRelease(void) override;

	void InitCollider(void) override;

	void SetPlayNumber(int n) { playNumber_ = n; }
private:
	virtual void MoveInput(void) {};
	int playNumber_;
};

