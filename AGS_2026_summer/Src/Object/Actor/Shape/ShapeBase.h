#pragma once
#include"../Collider/ColliderBase.h"

class ShapeBase :
	public ActorBase
{
public:
	ShapeBase(void);
	virtual ~ShapeBase(void);

protected:
	void SubLoad(void) override;
	void SubInit(void) override;
	void SubUpdate(void) override;
	void SubDraw(void) override;
	void SubRelease(void) override;
	int color_;
};