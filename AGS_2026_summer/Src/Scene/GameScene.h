#pragma once
#include "SceneBase.h"
#include<vector>
#include<memory>
#include"GameSelect/GameKind.h"

class ActorManager;
class CollisionManager;
class ContactEventManager;

class GameScene :
    public SceneBase
{
public:
    GameScene(void);
	GameScene(GameInfo info);
	~GameScene(void);

	void Load(void) override;
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;
	SCENE_ID GetSceneID(void)const override { return SCENE_ID::GAME; }
private:
#pragma region ä÷êî
	void SetContactEventRule(void);
	void SetContactEventCallback(void);
	void SetCollisionCollback(void);
#pragma endregion

#pragma region ïœêî
	std::unique_ptr<ActorManager> actorMng_;
	std::unique_ptr<CollisionManager>colMng_;
	GameInfo gameInfo_;
#pragma endregion

};

