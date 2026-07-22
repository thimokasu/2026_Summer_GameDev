#pragma once
#include "../../IState.h"
#include "../../StateBehavior.h"
#include "SwordFIghtCPU.h"


class SwordFightAttackCPU:
    public StateBehavior<SwordFIghtCPU>
{
public:
    //CharactorBaseにない処理を実装したい場合は
    // ではなく
    //StateBehaviorを継承し
    //テンプレートを使用して実装する
    void EnterT(SwordFIghtCPU* owner) override;
    void HandleInputT(SwordFIghtCPU* owner) override;
    void UpdateT(SwordFIghtCPU* owner) override;
    void ExitT(SwordFIghtCPU* owner) override;
};