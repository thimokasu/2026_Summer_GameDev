#include "GameBase.h"
#include"../../../Object/Actor/Manager/ActorManager.h"
#include"../../../Manager/System/Collision/CollisionManager.h"

GameBase::GameBase(ActorManager* actMng, CollisionManager* colMng)
	:
	actorMng_(actMng)
	,colMng_(colMng)
{
}

void GameBase::Load(void)
{
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
			colMng_->AddCollider(collider.get(), actor->GetEntityID());
		}
	}
	SubInit();
	InitSE();
	InitUI();
	InitCamera();
	SetContactEventRule();
	SetContactEventCallback();
	SetCollisionCollback();
}
void GameBase::Update(void)
{
	actorMng_->Update();
	colMng_->Update();
	colMng_->Resolve();
	SubUpdate();
}
void GameBase::Draw(void)
{
	actorMng_->Draw();
	SubDraw();
}
void GameBase::Release(void)
{
	actorMng_->Release();
	colMng_->ClearColliders();
	SubRelease();
}
