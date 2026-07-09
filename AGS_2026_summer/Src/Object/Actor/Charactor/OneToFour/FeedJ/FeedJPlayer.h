#pragma once
#include "../../CharactorBase.h"

class ItemBase;

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
        bool GetContactTrigger(void) { return isContactTrigger_; }

		void SetHoldItem(ItemBase* item) { holdItem_ = item; isHold_ = true; }
        void ReleaseHoldItem(void) { holdItem_ = nullptr; isHold_ = false; }
		ItemBase* GetHoldItem(void) { return holdItem_; } 
        void CreateState(void)override;

        void SetIsContact(bool flag) { isContact_ = flag; }
        bool GetIsContact(void) { return isContact_; }
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
    bool isContact_ = false;        //アイテムをドロップするのか置くのか判断するための接触状態
	bool isHold_ = false; //アイテムを持っているかどうか
	ItemBase* holdItem_ = nullptr; //持っているアイテムのポインタ
#pragma endregion

};

