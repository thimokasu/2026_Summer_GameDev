#pragma once
#include "../ActorBase.h"
#include<map>
#include<memory>
#include <typeindex>
#include <unordered_map>
#include"IState.h"

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
	virtual void InitRigidBody(void) {};
	virtual void CreateState(void) {};

	void SetPlayNumber(int n) { playNumber_ = n; }
	void SetUseController(int n) { useControllerNum_ = n; }
	int GetUseController(void) { return useControllerNum_; }

	void SetCanInput(bool flag) { canInput_ = flag; }
	bool GetCanInput(void) { return canInput_; }

	template<typename T>
	void AddState(std::unique_ptr<T>state);

	template<typename T>
	void ChangeState(void);	//遷移したいステートを<>のなかにクラス名を宣言

	template<typename T>
	T* GetState(void);

	template<typename  T>
	T* GetNowState(void);

	virtual void SetState(void) {};	//ステート初期化　AddState(std::make_unique<>());
protected:
	virtual void MoveInput(void) {};
	virtual void ReturnToIdle() {};		//オーバーライドでIdleStateへのChangeStateを実装しとく
	bool canInput_ = true;
	int playNumber_=0;	
	int useControllerNum_;
	std::unordered_map<std::type_index, std::unique_ptr<IState>>stateMap_;
	IState* currentState_ = nullptr;
};


template<typename T>
inline void CharactorBase::AddState(std::unique_ptr<T> state)
{
	stateMap_[typeid(T)] = std::move(state);
}

template<typename T>
inline void CharactorBase::ChangeState(void)
{
	auto it = stateMap_.find(typeid(T));
	if (it != stateMap_.end())
	{
		if (currentState_)currentState_->Exit(this);
		currentState_ = it->second.get();
		currentState_->Enter(this);
	}
}

template<typename T>
inline T* CharactorBase::GetState(void)
{
	auto it = stateMap_.find(typeid(T));
	if (it != stateMap_.end()) {
		return dynamic_cast<T*>(it->second.get());
	}
	return nullptr;
}

template<typename T>
inline T* CharactorBase::GetNowState(void)
{
	// 現在のステートが設定されていない場合は nullptr を返す
	if (!currentState_)
	{
		return nullptr;
	}

	// 現在のステートを指定された型 T に安全にキャストして返す
	return dynamic_cast<T*>(currentState_);
}

