#include "TestFactory.h"
#include"../../../Shape/Box.h"
#include"../../../Shape/Capsule.h"
#include"../../../../Common/RigidBody.h"
#include<memory>
#include<vector>

std::vector<std::unique_ptr<ActorBase>> TestFactory::CreateActors(void)
{
    std::vector<std::unique_ptr<ActorBase>> actors;

    VECTOR halfSize = { 1000, 10, 1000 };
    auto flor = std::make_unique<Box>(halfSize);
    flor->GetRigidBody().SetBodyType(Body::STATIC);
    flor->GetRigidBody().SetUseGravity(false);
	flor->SetEntityKind(EntityKind::STAGE);
    actors.push_back(std::move(flor));

    auto player = std::make_unique<Capsule>();
    player->GetRigidBody().SetBodyType(Body::DYNAMIC);
    player->GetRigidBody().SetUseGravity(true);
    player->GetRigidBody().SetMass(1);
    player->GetRigidBody().SetMoveSpeed(5);
	player->GetRigidBody().SetJumpForce(15);
	player->SetEntityKind(EntityKind::PLAYER);
    actors.push_back(std::move(player));
   
 return actors;
}
