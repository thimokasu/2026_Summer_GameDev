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

        void Test(void);
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
#pragma region ä÷êî
    void InitRigidBody(void)override;
    void ActionInput(void);
    void ReturnToIdle(void)override;
#pragma endregion


#pragma region ïœêî

#pragma endregion

};

