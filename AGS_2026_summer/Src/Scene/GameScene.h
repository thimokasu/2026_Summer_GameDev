#pragma once
#include "SceneBase.h"
#include<vector>
#include<memory>
#include"GameSelect/GameKind.h"

class ActorManager;

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

private:
#pragma region ä÷êî

#pragma endregion

#pragma region ïœêî
	std::unique_ptr<ActorManager> actorMng_;
	GameInfo gameInfo_;
#pragma endregion

};

