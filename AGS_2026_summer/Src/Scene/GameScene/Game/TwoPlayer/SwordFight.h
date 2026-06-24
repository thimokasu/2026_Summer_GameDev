#pragma once
#include "../GameBase.h"

class SwordFight :
	public GameBase
{
public:
	SwordFight(ActorManager* actMng, CollisionManager* colMng);
	~SwordFight(void);

	void SubLoad(void)override;
	void SubInit(void)override;
	void SubUpdate(void)override;
	void SubDraw(void)override;
	void SubRelease(void)override;

	void SetContactEventRule(void)override;
	void SetContactEventCallback(void)override;
	void SetCollisionCollback(void)override;

	void LoadUI(void)override;
	void LoadSE(void)override;
	void InitUI(void)override;
	void InitSE(void)override;
	void InitCamera(void)override;
private:

};