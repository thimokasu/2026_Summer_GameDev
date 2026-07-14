#pragma once
#include "../../ItemBase.h"
#include<memory>
#include<unordered_map>
#include<typeindex>
#include<map>
#include"../InterFace/FeedJ_Drop.h"
#include"../InterFace/FeedJ_ICooker.h"
#include"../Food/FoodKind.h"
class FeedJPlayer;
class FoodBase;
class StationBase;

class ContainerBase :
    public ItemBase,public FeedJ_Cooker
{
public:
    struct Slot
    {
        FoodBase* food_ = nullptr;
        FOOD_KIND kind = FOOD_KIND::NONE;
    };

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void OnPickUp(bool isPickUp) { isPickUp_ = isPickUp; }
    void OffPickUp(void) { isPickUp_ = false; }

    void AttachToPlayer(FeedJPlayer* player, VECTOR localOffset);
    void AttachToStation(StationBase* statoin, VECTOR localOffset);
    void Detach(void);
    void Cook(void)override;

    void SetSlot(std::vector<FoodBase*>foods);
    void SetSlot(FoodBase* food);
    FoodBase* GetHoldFood(void) { return foods_[0].food_; }//スロットが一つしかないコンテナ専用
    void CrearHoldFood(void);

    void SetIsAttachStation(bool flag) { isAttachStation_ = flag; }
    bool GetIsAttachStation(void) { return isAttachStation_; }

    bool GetCanSetSlot(void);

    bool GetCanCook(void) { return canCook_; }
protected:
#pragma region 関数
    virtual  void InitCollider(void)override;
    virtual void InitRigidBody(void)override;
    virtual void InitSlot(void) = 0;
#pragma endregion
#pragma region 変数
    bool isPickUp_ = true;   //持てるかどうか、お皿以外の調理器具は持てない
    bool canCook_ = false;
    VECTOR localOffset_ = { 0.0f,0.0f,0.0f }; //プレイヤーやステーションにくっつけるときのオフセット
    FeedJPlayer* player_ = nullptr;
    StationBase* station_ = nullptr;
    std::vector<Slot>foods_;
    bool isLock = false;        //調理中や皿に乗せた食材は持てない
    int maxSlot_ = 1;
    bool isAttachStation_;    //ステーションにアタッチされてるかどうか
    bool canSetSlot_ = true;
#pragma endregion
};

