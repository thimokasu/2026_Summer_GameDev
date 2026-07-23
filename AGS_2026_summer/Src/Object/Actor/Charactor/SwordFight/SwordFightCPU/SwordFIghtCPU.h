#pragma once
#include "../../CharactorBase.h"

class ItemBase;
class SwordFightPlayer;

class SwordFIghtCPU :
	public CharactorBase
{

public:

	SwordFIghtCPU(void);
	virtual ~SwordFIghtCPU(void);
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

	void OnDamage();

	void SetTarget(SwordFightPlayer* player)
	{
		target_ = player;
	}

	SwordFightPlayer* GetTarget()
	{
		return target_;
	}

	float GetDistanceToTarget();
	void LookTarget();


	enum  animType_CPU
	{
		NONE = -1,
		Idle_CPU,
		Walk_CPU,
		Attack_CPU,
		Damage_CPU,
		Block_CPU,
		BlockIdle_CPU,
		Lose_CPU,
		Sword_CPU,

		Max,
	};


	VECTOR moveVec_ = { 0.0f,0.0f,0.0f };

private:

	void UpdateSword();


	SwordFightPlayer* target_ = nullptr;

	int aiTimer_ = 0;

	float attackDistance_ = 120.0f;
	float findDistance_ = 400.0f;


	enum class STATE_CPU
	{
		IDLE_CPU,
		WALK_CPU,
		ATTACK_CPU,
		DAMAGE_CPU,
		BLOCK_CPU,
		LOSE_CPU,

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

	int rightHandFrameNo_;
	int leftHandFrameNo_;
};

