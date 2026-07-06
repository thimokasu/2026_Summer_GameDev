#pragma once
#include "../../ItemBase.h"
#include"../InterFace/FeedJ_ICookable.h"
#include"../InterFace/FeedJ_IThrowble.h"
#include"../InterFace/FeedJ_IPlaceble.h"
class FoodBase :
    public ItemBase,public FeedJ_ICookable,public FeedJ_IThrowble,public FeedJ_IPlaceble
{
public:  
    enum class STATE
    {
        IDLE,
		HOLD,
        DROPED,
        THROW,
        PUT,
        COOKING,
		COOKED,

        MAX,
    };
    FoodBase(void);
    ~FoodBase(void);

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;
    void InitCollider(void)override;


	void PlaceItem(ActorBase* owner)override;
	void Throw(ActorBase* owner)override;
	void OnCook(void)override;

	void OnPickUp(bool isPickUp) {isPickUp_ = isPickUp; }
	void OffPickUp(void) { isPickUp_ = false; }

private:
#pragma region ŠÖ”

#pragma endregion

#pragma region  •Ï”
	bool isPickUp_ = true;   //‚Ä‚é‚©‚Ç‚¤‚©A’²—Œã‚©‚ÂM‚Ìã‚É‚ ‚éê‡‚Í‚Ä‚È‚¢
	STATE state_ = STATE::IDLE;
	int modelIDtoCook_ = -1; //’²—Œã‚Ìƒ‚ƒfƒ‹ID
#pragma endregion


};

