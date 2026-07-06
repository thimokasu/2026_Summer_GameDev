#pragma once
#include "../../CharactorBase.h"

class ItemBaes;

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

        void OnContactTrigger(void) { isContactTrigger_ = true; }
        void OffContactTrigger(void) { isContactTrigger_ = false; }

		void SetHoldItem(ItemBaes* item) { holdItem_ = item; isHold_ = true; }
		void ReleaseHoldItem(void) { holdItem_ = nullptr; isHold_ = false; }
		ItemBaes* GetHoldItem(void) { return holdItem_; }
private:
    enum class STATE
    {
        IDLE,
        WALK,
        HOLD,
        HOLD_WALK,
        DASH,
        COOK,

        MAX,
    };
#pragma region 関数
    void InitRigidBody(void)override;
    void ActionInput(void);
    void ReturnToIdle(void)override;
#pragma endregion


#pragma region 変数
    bool isContactTrigger_ = false; //コンタクト用トリガーが起動してるかどうか
	bool isHold_ = false; //アイテムを持っているかどうか
	ItemBaes* holdItem_ = nullptr; //持っているアイテムのポインタ
#pragma endregion

};

