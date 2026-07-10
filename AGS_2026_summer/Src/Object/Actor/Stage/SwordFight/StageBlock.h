#pragma once
#include "../../ActorBase.h"

class StageBlock:public ActorBase
{
public:
    StageBlock(void);
    ~StageBlock(void);
    StageBlock(VECTOR pos);

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;

    void InitCollider(void)override;

    bool IsInsideStage(const VECTOR& pos) const;

private:
    VECTOR halfSize_ = { 1000.0f,80.0f,1000.0f };
};
