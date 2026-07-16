#pragma once
#include "../../StateBehavior.h"
#include "../SwordFightPlayer.h"

class SwordFight_Idle:
	public StateBehavior<SwordFightPlayer>
{
public:
    //CharactorBaseにない処理を実装したい場合は
    // ではなく
    //StateBehaviorを継承し
    //テンプレートを使用して実装する
    void EnterT(SwordFightPlayer* owner) override;
    void HandleInputT(SwordFightPlayer* owner) override;
    void UpdateT(SwordFightPlayer* owner) override;
    void ExitT(SwordFightPlayer* owner) override;
};

