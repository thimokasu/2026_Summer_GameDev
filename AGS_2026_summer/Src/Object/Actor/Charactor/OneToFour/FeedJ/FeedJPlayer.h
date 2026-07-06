#pragma once
#include "../../CharactorBase.h"
class FeedJPlayer :
    public CharactorBase
{
    public:
        FeedJPlayer(void);
        ~FeedJPlayer(void);

        void SubLoad(void) override;
        void SubInit(void) override;
        void SubUpdate(void) override;
        void SubDraw(void) override;
        void SubRelease(void) override;
        void InitCollider(void) override;
private:
    enum class STATE
    {
        IDLE,
        WALK,
        HOLD_WALK,
        DASH,
        COOK,

        MAX,
    };
    void MoveInput(void) override;
    void ActionInput(void);

#pragma region ïœêî

#pragma endregion

};

