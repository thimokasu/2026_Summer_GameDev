#pragma once
#include "../../ActorBase.h"
class ItemBase;

class StationBase :
    public ActorBase
{
public:
	StationBase(void);
	~StationBase(void);

	void SubLoad(void) override;
	void SubInit(void) override;
	void SubUpdate(void) override;
	void SubDraw(void) override;
	void SubRelease(void) override;
	void SetHoldItem(ItemBase* item){heldItem_ = item;	isHold_ = true;}
	void ReleaseHoldItem() { heldItem_ = nullptr;	isHold_ = false; }
	ItemBase* GetHoldItem() { return heldItem_; }


private:
	void InitCollider(void)override;
	void InitRigidBody(void)override;
#pragma region ïœêî
	ItemBase* heldItem_;
	bool isHold_ = false;
#pragma endregion

};

