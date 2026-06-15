#pragma once
#include"../GameBase.h"

class FindingJ :public GameBase
{
public:
	FindingJ(ActorManager* actMng, CollisionManager* colMng);
	~FindingJ(void);

	void SubLoad(void);
	void SubInit(void);
	void SubUpdate(void);
	void SubDraw(void);
	void SubRelease(void);

	void SetContactEventRule(void);
	void SetContactEventCallback(void);
	void SetCollisionCollback(void);

	void LoadUI(void);
	void LoadSE(void);
	void InitUI(void);
	void InitSE(void);
private:



};

