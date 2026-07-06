#include "UnicycleFactory.h"
#include<memory>
#include<vector>
#include"../../Shape/Box.h"
#include"../../Shape/Capsule.h"
#include"../../../Common/RigidBody.h"

#include"../../Stage/Test/TestFloor.h"
#include"../../Stage/Test/TestBox.h"

#include"../../Charactor/OnePlay/Test/TestPlayer.h"


UnicycleFactory::UnicycleFactory()
{
}

std::vector<std::unique_ptr<ActorBase>> UnicycleFactory::CreateActors(void)
{
    std::vector<std::unique_ptr<ActorBase>> actors;

    actors.push_back(std::make_unique<TestPlayer>());
    actors.push_back(std::make_unique<TestFloor>(VGet(0,-50,-50),VGet(0,0,0)));
    //actors.push_back(std::make_unique<TestFloor>(VGet(0,0,0),VGet(-0.5f, 0.0f, 0.0f)));
    //actors.push_back(std::make_unique<TestFloor>(VGet(0, 0, -200), VGet(0.5f, 0.0f, 0.0f)));
   // actors.push_back(std::make_unique<TestBox>(VGet(0.0f,40.0f,0.0f)));
   
 return actors;
}
