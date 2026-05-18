#pragma once
#include "ShapeBase.h"
class Capsule :
    public ShapeBase
{
    public:
    Capsule(void);
    Capsule(float radius, VECTOR localPosTop, VECTOR localPosDown);
	~Capsule(void);

protected:
#pragma region ä÷êî
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
    void InitCollider(void) override;
#pragma endregion
#pragma region ïœêî
	VECTOR localPosTop_;
	VECTOR localPosDown_;
    float radius_;
#pragma endregion
};

