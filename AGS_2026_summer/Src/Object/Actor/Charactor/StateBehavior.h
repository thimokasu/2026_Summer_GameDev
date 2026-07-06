#pragma once
#include "IState.h"
template<typename T>
class StateBehavior :
    public IState
{
public:
    // 派生先(T)に型キャストして呼び出す
    void Enter(CharactorBase* owner) override { EnterT(static_cast<T*>(owner)); }
    void HandleInput(CharactorBase* owner) override { HandleInputT(static_cast<T*>(owner)); }
    void Update(CharactorBase* owner) override { UpdateT(static_cast<T*>(owner)); }
    void Exit(CharactorBase* owner) override { ExitT(static_cast<T*>(owner)); }

    // 各ステートで実装する純粋仮想関数
    virtual void EnterT(T* owner) = 0;
    virtual void HandleInputT(T* owner) {}
    virtual void UpdateT(T* owner) = 0;
    virtual void ExitT(T* owner) = 0;
};

