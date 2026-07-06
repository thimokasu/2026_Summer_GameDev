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
    void MoveInput(void) override;
    void ActionInput(void);
};

