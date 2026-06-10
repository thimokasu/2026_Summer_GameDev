#pragma once
#include<memory>
#include"../../GameSelect/GameKind.h"

class ActorManager;
class CollisionManager;

class GameBase
{
public:
	GameBase(GameInfo info, ActorManager* actMng, CollisionManager* colMng);
	virtual ~GameBase(void) = default;

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

protected:
#pragma region ä÷êî
	virtual void SubLoad(void) {};
	virtual void SubInit(void) {};
	virtual void SubUpdate(void) {};
	virtual void SubDraw(void) {};
	virtual void SubRelease(void) {};

	virtual void SetContactEventRule(void) {};
	virtual void SetContactEventCallback(void) {};
	virtual void SetCollisionCollback(void) {};

	virtual void LoadUI(void) {};
	virtual void LoadSE(void) {};
	virtual void InitUI(void) {};
	virtual void InitSE(void) {};
#pragma endregion

#pragma region ïœêî
	GameInfo gameInfo_;
	ActorManager* actorMng_;
	CollisionManager* colMng_;
#pragma endregion
};

