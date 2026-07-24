#include "GameBase.h"
#include"../../../Object/Actor/Manager/ActorManager.h"
#include"../../../Manager/System/Collision/CollisionManager.h"
#include"../../../Object/Actor/Collider/ColliderBase.h"
#include "../../../Object/Actor/Camera/Camera.h"

GameBase::GameBase(ActorManager* actMng, CollisionManager* colMng)
	:
	actorMng_(actMng)
	,colMng_(colMng)
{
}



void GameBase::Load(GameInfo info)
{
	gameInfo_ = info;
	SubLoad();
	LoadSE();
	LoadUI();
}
void GameBase::Init(void)
{
	actorMng_->Init();
	for (auto& actor : actorMng_->GetActors())
	{
		for (const auto& [shape, collider] : actor->GetOwnColliders())
		{
			colMng_->AddCollider(collider.get(), actor->GetEntityID(),collider->GetColliderInfo().entityKind_);
		}
	}
	SubInit();
	InitCamera();
	SetContactEventRule();
	SetContactEventCallback();
	SetCollisionCollback();
	SetEventCallBack();
	InitSE();
	InitUI();
}
void GameBase::Update(void)
{
	if (isUpdate_)
	{
	actorMng_->Update();
	colMng_->Update();
	colMng_->Resolve();
	}
	SubUpdate();
}
void GameBase::Draw(void)
{
	actorMng_->Draw();
	//colMng_->DebugDraw();
	SubDraw();
}
void GameBase::Release(void)
{
	actorMng_->Release();
	colMng_->ClearColliders();
	SubRelease();
}

void GameBase::SetCollisionCollback(void)
{
	auto onBeginContact = [this](uint32_t a,EntityKind kindA, uint32_t b,EntityKind kindB)
		{
			Entity entA{ a, kindA };
			Entity entB{ b, kindB };
			EventManager::GetInstance().OnBeginContact(entA, entB, CollisionResult{});
		};
	auto onEndContact = [this](uint32_t a,EntityKind kindA, uint32_t b,EntityKind kindB)
		{
			Entity entA{ a,kindA  };
			Entity entB{ b, kindB };
			EventManager::GetInstance().OnEndContact(entA, entB, CollisionResult{});
		};
	auto onStayContact = [this](uint32_t a, EntityKind kindA, uint32_t b, EntityKind kindB)
		{
			Entity entA{ a,kindA };
			Entity entB{ b,kindB };
			EventManager::GetInstance().OnStayContact(entA, entB, CollisionResult{});
		};
	colMng_->SetContactCallbacks(onBeginContact, onEndContact,onStayContact);
}

void GameBase::AddCollider(ActorBase* actor)
{
	for (const auto& [shape, col] : actor->GetOwnColliders())
	{
		colMng_->AddCollider(col.get(), actor->GetEntityID(),col->GetColliderInfo().entityKind_);
	}
}
