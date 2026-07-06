#pragma once
#include "IState.h"
class IdleState :
    public IState
{
public:
    void Enter(CharactorBase* owner) override;
    void HandleInput(CharactorBase* owner) override;
    void Update(CharactorBase* owner) override;
    void Exit(CharactorBase* owner) override;
};

