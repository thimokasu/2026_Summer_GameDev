#include "GameBase.h"
#include"../../../Object/Actor/Manager/ActorManager.h"
#include"../../../Manager/System/Collision/CollisionManager.h"

GameBase::GameBase(GameInfo info, ActorManager* actMng, CollisionManager* colMng)
	:gameInfo_(info)
	,actorMng_(actMng)
	,colMng_(colMng)
{
}

void GameBase::Load(void)
{
	actorMng_->Load(gameInfo_);
	SubLoad();
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
