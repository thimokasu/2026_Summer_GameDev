#pragma once
#include "../../ActorBase.h"
class AthleticMoveFloor :
    public ActorBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;
    void SetStartPos(VECTOR pos) { startPos_ = pos; }
private:
    void InitRigidBody(void)override; 
    float timer_ = 0.0f;       // 経過時間
    float speed_ = 0.05f;      // 動く速さ
    float amplitude_ = 20.0f; // 動く幅（左右に200ずつ）
    VECTOR startPos_;          // 初期位置
};

