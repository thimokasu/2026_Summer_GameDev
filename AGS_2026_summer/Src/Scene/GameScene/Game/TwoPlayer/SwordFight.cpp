#include "SwordFight.h"

#include"../../../../Manager/Game/SceneManager.h"

#include"../../../../Object/Actor/Manager/ActorManager.h"

#include"../../../../Object/Actor/Camera/Camera.h"



SwordFight::SwordFight(ActorManager* actMng, CollisionManager* colMng)
{
}

SwordFight::~SwordFight(void)
{
}

void SwordFight::SubLoad(void)
{
}

void SwordFight::SubInit(void)
{
}

void SwordFight::SubUpdate(void)
{
}

void SwordFight::SubDraw(void)
{
}

void SwordFight::SubRelease(void)
{
}

void SwordFight::SetContactEventRule(void)
{
	//チャンバラが当たった時にイベント発生の設定
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::SWORD, GameEventType::HIT_REACTION);
	EventManager::GetInstance().SetEventRule(EntityKind::CPU, EntityKind::SWORD, GameEventType::HIT_REACTION);
}

void SwordFight::SetContactEventCallback(void)
{
	//イベントのコールバック関数の設定
	EventManager::GetInstance().SetContactEventCallback(GameEventType::HIT_REACTION, [this](const ContactRule& rule)
		{
		

		}
	);

}

void SwordFight::SetCollisionCollback(void)
{
	auto onBeginContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorMng_->GetEntityKind(a) };
			Entity entB{ b, actorMng_->GetEntityKind(b) };
			EventManager::GetInstance().OnBeginContact(entA, entB, CollisionResult{});
		};
	auto onEndContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorMng_->GetEntityKind(a) };
			Entity entB{ b, actorMng_->GetEntityKind(b) };
			EventManager::GetInstance().OnEndContact(entA, entB, CollisionResult{});
		};
	colMng_->SetContactCallbacks(onBeginContact, onEndContact);
}

void SwordFight::LoadUI(void)
{
}

void SwordFight::LoadSE(void)
{
}

void SwordFight::InitUI(void)
{
}

void SwordFight::InitSE(void)
{
}

void SwordFight::InitCamera(void)
{
}
