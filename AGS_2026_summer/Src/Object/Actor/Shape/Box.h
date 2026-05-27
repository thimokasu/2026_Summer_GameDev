#pragma once
#include "ShapeBase.h"

class Box :
    public ShapeBase
{
    public:
    Box(void);
	Box(const VECTOR& halfSize);
    ~Box(void);

private:
	void SubLoad(void) override;
	void SubInit(void) override;
	void SubUpdate(void) override;
	void SubDraw(void) override;
	void SubRelease(void) override;

	void InitCollider(void) override;

	VECTOR halfSize_;

};

