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

	void InCreaseStateFrame(void) { stateFrame_++; }	//現ステート経過時間増加
	void DecreaseIdleTime(void) { idleTime_--; }	//IdleStateに切り替わるまでの時間を減少

	int GetIdleTime(void) const { return idleTime_; }
	const char* GetName(void) { return typeid(*this).name(); }
	bool GetIsLoop(void) const { return isLoop_; }
	int GetNextInputStartTime(void) { return nextInputStartTime_; }
	int GetStateFrame(void) { return stateFrame_; }
	void OnCanChange(void) { canChange_ = true; }
protected:

	bool canChange_ = false;//ステート経過中に途中で別ステートに切り替えれるかどうか
	bool isLoop_ = false;	//ループするかどうか（しない場合idleTimeが０になったらIdleStateに遷移）
	int idleTime_ = 0;		//IdleStateへの遷移するまでの時間
	int stateFrame_ = 0;	//現ステートの経過フレーム数
	int nextInputStartTime_ = 0;	//canChangeをOnOffするための時間　０で即抜け
};
