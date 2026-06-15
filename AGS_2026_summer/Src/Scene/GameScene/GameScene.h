#pragma once
#include "../SceneBase.h"
#include<vector>
#include<memory>
#include"../GameSelect/GameInfo.h"
#include"../GameScene/MiniGameFactory/MiniGameFactory.h"
class ActorManager;
class CollisionManager;
class ContactEventManager;
class MiniGameFactory;
class GameBase;

class GameScene :
    public SceneBase
{
public:
    GameScene(void);
	GameScene(GameInfo info);
	~GameScene(void);

	void SubLoad(void) override;
	void SubInit(void) override;
	void SubUpdate(void) override;
	void SubDraw(void) override;
	void SubRelease(void) override;
	SCENE_ID GetSceneID(void)const override { return SCENE_ID::GAME; }
private:
#pragma region ä÷êî
	void SetContactEventRule(void);
	void SetContactEventCallback(void);
	void SetCollisionCollback(void);
	void CreateMiniGame(GAME_KIND kind);
#pragma endregion

#pragma region ïœêî
	std::unique_ptr<ActorManager> actorMng_;
	std::unique_ptr<CollisionManager>colMng_;
	std::unique_ptr<GameBase> miniGame_;
	GameInfo gameInfo_;
	std::unique_ptr<MiniGameFactory>miniGameFactory_;
#pragma endregion

};

