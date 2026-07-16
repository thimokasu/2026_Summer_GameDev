#pragma once
#include "../CharactorBase.h"

class ItemBase;

class SwordFightPlayer :
	public CharactorBase
{
public:


	SwordFightPlayer(void);
	virtual ~SwordFightPlayer(void);
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

	enum  animType
	{
		NONE=-1,
		Idle,
		Walk,
		Attack,
		Damage,
		Block,
		BlockIdle,
		Lose,
		Sword,

		Max,
	};


	VECTOR moveVec_ = { 0.0f,0.0f,0.0f };



private:


	enum class STATE
	{
		IDLE,
		WALK,
		ATTACK,
		DAMAGE,
		BLOCK,
		LOSE,

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
	ItemBase* holdItem_ = nullptr; //持っているアイテムのポインタ
#pragma endregion
};

