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


#include"../../Actor/Factory/ActorFactory/ActorFactoryBase.h"
#include"../../Actor/Factory/ActorFactory/FindingJ/Stage1Factory.h"
#include"../../Actor/Factory/ActorFactory/FindingJ/Stage2Factory.h"
#include"../../Actor/Factory/ActorFactory/FindingJ/Stage3Factory.h"

ActorManager::ActorManager()
{
}

ActorManager::~ActorManager()
{
}



void ActorManager::Load(void)
{
}

void ActorManager::Load(GAMEKIND kind)
{
	auto player = std::make_shared<Capsule>(8.0f, VGet(0.0f, 10.0f, 0.0f), VGet(0.0f, -10.0f, 0.0f));
	player->SetEntityKind(EntityKind::PLAYER);
	player->GetTransform().pos = VGet(0.0f, 100.0f, 0.0f);
	auto rb = std::make_shared<RigidBody>();
	rb->SetBodyType(RigidBody::BodyType::DYNAMIC);
	rb->SetMoveSpeed(5);
	rb->SetJumpPower(30);
	player->AddComponent(rb);
	player->AddComponent(std::make_shared<PlayerInputComponent>(
		KEY_INPUT_W, KEY_INPUT_S,
		KEY_INPUT_A, KEY_INPUT_D,
		KEY_INPUT_Q, KEY_INPUT_E));
	player->SetEntityKind(EntityKind::PLAYER);
	player->GetComponent<PlayerInputComponent>().SetJumpKey(KEY_INPUT_SPACE);
	actors_.push_back(player);

	SetFactory(kind);
	
	for(auto & actor : actorFactory_->CreateActors())
	{
		actors_.push_back(actor);
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

void ActorManager::SetFactory(GAMEKIND kind)
{
	switch (kind)
	{
	case GAMEKIND::NONE:
		break;
	case GAMEKIND::FINDINGJ_STAGE1:
		actorFactory_ = std::make_unique<Stage1Factory>();
		break;
	case GAMEKIND::FINDINGJ_STAGE2:
		actorFactory_ = std::make_unique<Stage2Factory>();
		break;
	case GAMEKIND::FINDINGJ_STAGE3:
		actorFactory_ = std::make_unique<Stage3Factory>();
		break;
	default:
		break;
	}
}


