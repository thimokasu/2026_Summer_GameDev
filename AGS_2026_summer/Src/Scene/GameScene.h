#pragma once
#include "SceneBase.h"

#include<vector>
#include<memory>

#include"../Manager/System/CollisionSystem/CollisionSystem.h"
#include"../Manager/System/ContactSystem/ContactSystem.h"
#include"../Manager/System/ContactSystem/GameContactSystem.h"
#include"../Manager/System/MoveInputSystem/MoveInputSystem.h"
#include"../Manager/System/PhysicsSystem/PhysicsSystem.h"

#include"../Manager/Generic/KeyManager.h"

#include"../Object/Actor/Manager/ActorManager.h"
#include"GameSelect/GameKind.h"
class GameScene :
    public SceneBase
{
public:
    GameScene(void);
	GameScene(GAMEKIND kind);
    ~GameScene(void)override;

    void Load(void)override;
    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;

private:
    CollisionSystem collisionSystem_;
    ContactSystem contactSystem_;
    GameContactSystem gameContactSystem_;
    PhysicsSystem physicsSystem_;


    MoveInputSystem moveInputSystem_;

    ActorManager actorManager_;
    GAMEKIND gameKind_;

};

