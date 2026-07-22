#include "SwordFight.h"

#include"../../../../Manager/Game/SceneManager.h"

#include"../../../../Object/Actor/Manager/ActorManager.h"

#include"../../../../Object/Actor/Camera/Camera.h"

#include"../../../../Object/Actor/Charactor/SwordFight/SwordFightPlayer.h"
#include"../../../../Object/UI/FindingJ/GameMessageUI.h"

#include"../../../../Object/UI/FindingJ/Timer.h"

#include "../../../../Object/Actor/Charactor/SwordFight/SwordFIghtCPU/SwordFIghtCPU.h"


SwordFight::SwordFight(ActorManager* actMng, CollisionManager* colMng)
{
	actorMng_ = actMng;
	colMng_ = colMng;
}

SwordFight::~SwordFight(void)
{
}

void SwordFight::SubLoad(void)
{
}

void SwordFight::SubInit(void)
{
	SetContactEventRule();
	SetContactEventCallback();
	SetCollisionCollback();

	InitCamera();
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
			Entity entityA =
				rule.contactEvent_.entityA;

			Entity entityB =
				rule.contactEvent_.entityB;


			ActorBase* actorA =
				actorMng_->FindActorByID(entityA.entityID_);

			ActorBase* actorB =
				actorMng_->FindActorByID(entityB.entityID_);


			if (actorA == nullptr || actorB == nullptr)
			{
				return;
			}


			// 剣が当たった相手を探す
			ActorBase* target = nullptr;
			ActorBase* sword = nullptr;


			if (entityA.entityKind_ == EntityKind::SWORD)
			{
				sword = actorA;
				target = actorB;
			}
			else if (entityB.entityKind_ == EntityKind::SWORD)
			{
				sword = actorB;
				target = actorA;
			}


			if (target == nullptr || sword == nullptr)
			{
				return;
			}


			// 吹っ飛ぶ方向
			VECTOR dir =
				VSub(
					target->GetTransform().pos,
					sword->GetTransform().pos);


			dir.y = 0;


			if (VSize(dir) > 0)
			{
				dir = VNorm(dir);
			}


			// 吹っ飛び力
			VECTOR force =
			{
				dir.x * 15.0f,
				12.0f,
				dir.z * 15.0f
			};


			target->GetRigidBody()
				.AddForce(force);


		});

}

void SwordFight::SetCollisionCollback(void)
{
	DrawFormatString(
		0,
		150,
		0xffffff,
		"Collision");
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
	SceneManager::GetInstance().GetCamera().ChangeMode(Camera::MODE::FOLLOW);
	auto player = actorMng_->FindActorsByKind(EntityKind::PLAYER);
	for (auto& p : player)
	{
		auto& player = dynamic_cast<SwordFightPlayer&>(*p);
		SceneManager::GetInstance().GetCamera().SetFollow(&player.GetTransform());
	}
	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(0.73f, 0.0f, 0.0f));
	SceneManager::GetInstance().GetCamera().StopMove();
}
