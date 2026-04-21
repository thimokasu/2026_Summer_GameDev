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

#include "../../../Net/NetManager.h"

ActorManager::ActorManager()
{
}

ActorManager::~ActorManager()
{
}



void ActorManager::Load(void)
{
	std::shared_ptr<Box>box = std::make_shared<Box>();
	box->GetTransform().pos = VGet(0.0f, 200.0f, 0.0f);
	box->AddComponent(std::make_shared<PlayerInputComponent>(
		KEY_INPUT_W, KEY_INPUT_S,
		KEY_INPUT_A, KEY_INPUT_D,
		KEY_INPUT_Q, KEY_INPUT_E)
	);
	auto rb = std::make_shared<RigidBody>();
	rb->SetBodyType(RigidBody::BodyType::DYNAMIC);
	rb->SetMass(10.0f);
	rb->SetUseGravity(true);
	box->AddComponent(rb);
	box->SetEntityKind(EntityKind::STAGE);
	actors_.push_back(box);

	box = std::make_shared<Box>();
	box->GetTransform().pos = VGet(400.0f, 200.0f, 0.0f);
	box->AddComponent(std::make_shared<PlayerInputComponent>(
		KEY_INPUT_T, KEY_INPUT_G,
		KEY_INPUT_F, KEY_INPUT_H,
		KEY_INPUT_R, KEY_INPUT_Y)
	);
	rb = std::make_shared<RigidBody>();
	rb->SetBodyType(RigidBody::BodyType::DYNAMIC);
	rb->SetMass(1.0f);
	rb->SetUseGravity(true);
	box->AddComponent(rb);
	box->SetEntityKind(EntityKind::STAGE);
	actors_.push_back(box);

	std::shared_ptr<Floor> floor = std::make_shared<Floor>(VGet(1000.0f, 5.0f, 1000.0f));
	floor->GetTransform().pos = VGet(0, -100, 0);
	rb = std::make_shared<RigidBody>();
	rb->SetBodyType(RigidBody::BodyType::STATIC);
	rb->SetMass(0.0f);
	floor->AddComponent(rb);

	actors_.push_back(floor);
}

std::map<int, NET_JOIN_USER> ActorManager::TestLoad(void)
{
	auto& users = NetManager::GetInstance().GetNetUsers();

	std::map<int, NET_JOIN_USER> data = {};

	for (auto& [id, user] : users)
	{
		std::shared_ptr<Box>box = std::make_shared<Box>();
		box->GetTransform().pos = VGet(0.0f, 200.0f, 0.0f);
		actors_.push_back(box);
		box->AddComponent(std::make_shared<PlayerInputComponent>(
			KEY_INPUT_W, KEY_INPUT_S,
			KEY_INPUT_A, KEY_INPUT_D,
			KEY_INPUT_Q, KEY_INPUT_E)
		);
		auto rb = std::make_shared<RigidBody>();
		rb->SetBodyType(RigidBody::BodyType::DYNAMIC);
		rb->SetMass(10.0f);
		rb->SetUseGravity(true);
		box->AddComponent(rb);
		box->SetEntityKind(EntityKind::STAGE);

		data = { {id, user} };
	}

	return data;
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



