#include "ActorManager.h"
#include<DxLib.h>

#include"../Shape/Box.h"
#include"../Shape/Capsule.h"
#include"../Shape/Sphere.h"
#include"../Shape/ShapeBase.h"

#include"../Component/PlayerInputComponent/PlayerInputComponent.h"
#include"../Component/RigidBodyComponent/RigidBody.h"

#include"../ActorBase.h"
#include"../../Common/Transform.h"
#include"../Floor/Floor.h"
#include"../Camera/Camera.h"

ActorManager::ActorManager()
{
}

ActorManager::~ActorManager()
{
}



void ActorManager::Load(void)
{
	auto actors = actorFactory_.CreateActor(GAMEKIND::FINDINGJ_STAGE1);
	for (auto a : actors)
	{
		actors_.push_back(a);
	}
}

void ActorManager::Init(void)
{
	for (auto& actor : actors_)
	{
		actor->Init();
		actor->SetEntityId(entityId_++);	
		
	}
}

void ActorManager::Update(void)
{
	BindId2Kind();
	for (auto& actor : actors_)
	{
		actor->Update();
	}
}

void ActorManager::Draw(void)
{
	for (auto& actor : actors_)
	{
		actor->Draw();
		for (const auto& [shape, collider] : actor->GetOwnColliders())
		{
			collider->Draw();
		}
	}
}

void ActorManager::Release(void)
{
	for (auto& actors_ : actors_)
	{
		actors_->Release();
	}
	actors_.clear();
}


EntityKind ActorManager::GetKind(int entityId_)
{
	return id2Kind_[entityId_];
}

void ActorManager::BindId2Kind(void)
{
	for (auto& obj : actors_)
	{
		id2Kind_[obj->GetEntityId()] = obj->GetEntityKind();
	}
}



