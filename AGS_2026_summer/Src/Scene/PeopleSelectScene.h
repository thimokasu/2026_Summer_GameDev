#pragma once
#include "SceneBase.h"
class PeopleSelectScene :
    public SceneBase
{
	public:
	PeopleSelectScene();
	~PeopleSelectScene();
    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;
private:
};

