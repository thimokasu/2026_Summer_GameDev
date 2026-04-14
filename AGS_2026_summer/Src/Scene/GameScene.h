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

class GameScene :
    public SceneBase
{
public:
    GameScene(void);
    ~GameScene(void)override;

    void Load(void)override;
    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;

private:
    std::vector<std::shared_ptr<ActorBase>>actors_;

    CollisionSystem collisionSystem_;
    ContactSystem contactSystem_;
    GameContactSystem gameContactSystem_;
    PhysicsSystem physicsSystem_;


    MoveInputSystem moveInputSystem_;
    
    int EntityId = 0;

};

