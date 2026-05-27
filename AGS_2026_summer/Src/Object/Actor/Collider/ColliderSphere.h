#pragma once
#include "ColliderBase.h"
class ColliderSphere :
    public ColliderBase
{
    public:
    //コンストラクタ
    ColliderSphere(ColliderInfo& info, float radius, ActorBase& actor);
    ColliderSphere(ColliderInfo& info, float radius, ActorBase& actor, int debugColor);
    //半径取得
    float GetRadius(void)const { return radius_; }
    //半径設定
	void SetRadius(float radius) { radius_ = radius; }

private:
	float radius_;
	void DrawDebug(int color) override;
};

