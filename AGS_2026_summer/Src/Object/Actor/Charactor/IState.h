#pragma once
#include<typeindex>

class CharactorBase;

class IState
{
public:
	virtual ~IState(void) {};

	virtual void Enter(CharactorBase* owner) = 0;

	virtual void HandleInput(CharactorBase* owner) {};

	virtual void Update(CharactorBase* owner) = 0;

	virtual void Exit(CharactorBase* owner) = 0;

	void InCreaseStateFrame(void) { stateFrame_++; }
	void DecreaseIdleTime(void) { idleTime_--; }

	int GetIdleTime(void) const { return idleTime_; }
	const char* GetName(void) { return typeid(*this).name(); }
	bool GetIsLoop(void) const { return isLoop_; }
	int GetNextInputStartTime(void) { return nextInputStartTime_; }
	int GetStateFrame(void) { return stateFrame_; }
	void OnCanChange(void) { canChange_ = true; }
protected:

	bool canChange_ = false;
	bool isLoop_ = false;
	int idleTime_ = 0;
	int stateFrame_ = 0;
	int nextInputStartTime_ = 0;
};
