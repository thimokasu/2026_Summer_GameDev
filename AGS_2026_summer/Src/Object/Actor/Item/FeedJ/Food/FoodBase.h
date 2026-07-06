#pragma once
#include "../../ItemBase.h"
#include"../InterFace/FeedJ_ICookable.h"
#include"../InterFace/FeedJ_IThrowble.h"
#include"../InterFace/FeedJ_IPlaceble.h"
class FoodBase :
    public ItemBase,public FeedJ_ICookable,public FeedJ_IThrowble,public FeedJ_IPlaceble
{
public:   
    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;
    void InitCollider(void)override;


private:
	void Throw(ActorBase* owner)override;


};

