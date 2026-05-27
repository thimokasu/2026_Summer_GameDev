#pragma once
#include "ShapeBase.h"
class Sphere :
    public ShapeBase
{
    public:
    Sphere(void);
    Sphere(float radius);
	~Sphere(void);

private:
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
    void InitCollider(void) override;
	float radius_;
};

