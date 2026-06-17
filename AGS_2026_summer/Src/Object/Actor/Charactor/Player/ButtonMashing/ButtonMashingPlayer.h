#pragma once
#include "../../CharactorBase.h"
#include"../../../../../Scene/GameScene/Game/FourPlayer/ButtonMashing/ButtonKind.h"
class ButtonMashingPlayer :
    public CharactorBase
{
public:
    ButtonMashingPlayer(void);
    ~ButtonMashingPlayer(void)override;

    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;

    void SetActiveButton(Button b) { activeButton_ = b; }
    int GetMashCount(void) { return mashCount_; }
private:
    int mashCount_;//òAë≈êî
    Button activeButton_;

    void InputUpdate(void);
};

