#include "GameScene.h"
#include<DxLib.h>

#include"../Manager/Game/SceneManager.h"
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Generic/KeyManager.h"

#include"../Manager/System/PhysicsSystem/PhysicsSystem.h"
#include"../Manager/System/CollisionSystem/CollisionSystem.h"
#include"../Manager/System/ContactSystem/ContactSystem.h"
#include"../Manager/System/ContactSystem/GameContactSystem.h"
#include"../Manager/System/MoveInputSystem/MoveInputSystem.h"


#include"../Object/Actor/Shape/Box.h"
#include"../Object/Actor/Shape/Capsule.h"
#include"../Object/Actor/Shape/Sphere.h"
#include"../Object/Actor/Shape/ShapeBase.h"

#include"../Object/Actor/Component/PlayerInputComponent/PlayerInputComponent.h"
#include"../Object/Actor/Component/RigidBodyComponent/RigidBody.h"


#include"../Object/Actor/Floor/Floor.h"
#include"../Object/Actor/Camera/Camera.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

template<typename T>
std::vector<std::shared_ptr<T>> ObjSearch(const std::vector<std::shared_ptr<ActorBase>>& objects)
{
	static_assert(std::is_base_of_v<ActorBase, T>);

	std::vector<std::shared_ptr<T>> out;
	out.reserve(objects.size());

	for (const auto& obj : objects)
	{
		if (!obj) continue;

		if (auto casted = std::dynamic_pointer_cast<T>(obj))
		{
			out.push_back(casted);
		}
	}
	return out;
}

void GameScene::Load(void)
{
	std::shared_ptr<Box>box = std::make_shared<Box>();
	box->GetTransform().pos = VGet(300.0f, 200.0f, 0.0f);
	actors_.push_back(box);
	box->AddComponent(std::make_shared<PlayerInputComponent>(
		KEY_INPUT_W, KEY_INPUT_S,
		KEY_INPUT_A, KEY_INPUT_D,
		KEY_INPUT_Q, KEY_INPUT_E)
	);
	auto rb = std::make_shared<RigidBody>();
	rb->SetBodyType(RigidBody::BodyType::DYNAMIC);
	rb->SetMass(1.0f);
	rb->SetUseGravity(true);
	box->AddComponent(rb);

	box = std::make_shared<Box>();
	box->GetTransform().pos = VGet(300.0f, 200.0f, 0.0f);
	actors_.push_back(box);
	rb = std::make_shared<RigidBody>();
	rb->SetBodyType(RigidBody::BodyType::DYNAMIC);
	rb->SetMass(1.0f);
	rb->SetUseGravity(true);
	box->AddComponent(rb);

	std::shared_ptr<Floor> floor = std::make_shared<Floor>(VGet(1000.0f, 5.0f, 1000.0f));
	floor->GetTransform().pos = VGet(0, -100, 0);
	rb = std::make_shared<RigidBody>();
	rb->SetBodyType(RigidBody::BodyType::STATIC);
	rb->SetMass(0.0f);
	floor->AddComponent(rb);

	actors_.push_back(floor);
}

void GameScene::Init(void)
{
	auto onBeginContact = [this](uint32_t a, uint32_t b)
		{
			contactSystem_.OnBeginContact(a, b, CollisionResult{});
		};
	auto onEndContact = [this](uint32_t a, uint32_t b)
		{
			contactSystem_.OnEndContact(a, b, CollisionResult{});
		};

	for (auto& actor : actors_)
	{
		actor->Init();
		actor->SetEntityId(EntityId++);
		collisionSystem_.AddCollider(actor->GetOwnColliders());
	}
}

void GameScene::Update(void)
{
	for (auto& actor : actors_)
	{
		actor->Update();
	}

	moveInputSystem_.Update(actors_);
	physicsSystem_.Update(actors_);

	collisionSystem_.Update();
	gameContactSystem_.Update();

	physicsSystem_.Resolve(actors_,collisionSystem_.GetCollisionMainfold());

}

void GameScene::Draw(void)
{
	DrawString(0, 0, "game", 0xffffff);

	for (auto& actor : actors_)
	{
		actor->Draw();
		for (const auto& [shape, collider] : actor->GetOwnColliders())
		{
			collider->Draw();
		}
	}
}

void GameScene::Release(void)
{
	for(auto&actors_: actors_)
	{
		actors_->Release();
	}
	actors_.clear();
}
