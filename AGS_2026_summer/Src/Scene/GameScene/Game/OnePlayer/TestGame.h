#pragma once
#include "../GameBase.h"
class TestGame :
    public GameBase
{
public	:
    TestGame(ActorManager* actMng, CollisionManager* colMng);
    ~TestGame(void)override;

	void SubLoad(void)override;
	void SubInit(void)override;
	void SubUpdate(void)override;
	void SubDraw(void)override;
	void SubRelease(void)override;

	void SetContactEventRule(void)override;
	void SetContactEventCallback(void)override;
	void SetCollisionCollback(void)override;
	void SetEventCallBack(void)override;

	void LoadUI(void)override;
	void LoadSE(void)override;
	void InitUI(void)override;
	void InitSE(void)override;
	void InitCamera(void)override;
};

