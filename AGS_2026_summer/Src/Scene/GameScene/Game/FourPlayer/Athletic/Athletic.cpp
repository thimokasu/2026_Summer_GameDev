#include "Athletic.h"
#include"../../../../../Object/Actor/Manager/ActorManager.h"
#include"../../../../../Object/Actor/EntityKind.h"
#include"../../../../../Object/Actor/Stage/Athletic/AthleticHeaders.h"
#include"../../../../../Object/Actor/Charactor/FourPlayer/Athletic/AthleticPlayer.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../../../Object/Actor/Camera/Camera.h"
Athletic::Athletic(ActorManager* actMng, CollisionManager* colMng):GameBase(actMng,colMng)
{
}

Athletic::~Athletic(void)
{
}

void Athletic::SubLoad(void)
{

}

void Athletic::SubInit(void)
{
	isUpdate_ = true;
}

void Athletic::SubUpdate(void)
{
	auto actors = actorMng_->FindActorsByKind(EntityKind::PLAYER);
	bool finishFlag = true;
	for (auto a : actors)
	{
		auto p = dynamic_cast<AthleticPlayer*>(a);
		if (p->GetCanInput())
		{
			finishFlag = false;
			break;
		}
	}
	if (finishFlag)
	{
		EventManager::GetInstance().TriggerEvent(GameEventType::FINISH);
	}
	auto pos = SceneManager::GetInstance().GetCamera().GetTransform().pos;
	SceneManager::GetInstance().GetCamera().SetCameraPos(VAdd(pos, VGet(0.1f, 0, 0)));
}

void Athletic::SubDraw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Camera Position: %f, %f, %f",
		SceneManager::GetInstance().GetCamera().GetPos().x,
		SceneManager::GetInstance().GetCamera().GetPos().y,
		SceneManager::GetInstance().GetCamera().GetPos().z);
	DrawFormatString(0, 20, 0xffffff, "Camera Angles: %f, %f, %f",
		SceneManager::GetInstance().GetCamera().GetAngles().x,
		SceneManager::GetInstance().GetCamera().GetAngles().y,
		SceneManager::GetInstance().GetCamera().GetAngles().z);
}

void Athletic::SubRelease(void)
{
}

void Athletic::SetContactEventRule(void)
{
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::ATHLETIC_GOAL, GameEventType::ATHLETIC_GOAL);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::ATHLETIC_CLOUD, GameEventType::ATHLETIC_CLOUD);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::PLAYER, GameEventType::ATHLETIC_PLAYER_ON);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::ATHLETIC_FALL, GameEventType::ATHLETIC_FALL);
}

void Athletic::SetContactEventCallback(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::ATHLETIC_GOAL, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			AthleticPlayer* player = nullptr;
			AthleticGoal* goal = nullptr;
			if (entityKindA == EntityKind::PLAYER) { player = dynamic_cast<AthleticPlayer*>(actorA); goal = dynamic_cast<AthleticGoal*>(actorB); }
			else if (entityKindB == EntityKind::PLAYER) { player = dynamic_cast<AthleticPlayer*>(actorB); goal = dynamic_cast<AthleticGoal*>(actorA); }
			if (!player || !goal)return;
			player->SetCanInput(false);
			clearPlayers_.push_back(player);
		});
	EventManager::GetInstance().SetContactEventCallback(GameEventType::ATHLETIC_CLOUD, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			AthleticPlayer* player = nullptr;
			AthleticCloud* cloud = nullptr;
			AthleticMiniCloud* mcloud = nullptr;
			bool mcloudFlag = false;
			if (entityKindA == EntityKind::PLAYER)
			{ 
				player = dynamic_cast<AthleticPlayer*>(actorA); 
				cloud = dynamic_cast<AthleticCloud*>(actorB);
				if (!cloud)
				{
					mcloud = dynamic_cast<AthleticMiniCloud*>(actorB);
					mcloudFlag = true;
				}
			}
			else if (entityKindB == EntityKind::PLAYER)
			{
				player = dynamic_cast<AthleticPlayer*>(actorB); 
				cloud = dynamic_cast<AthleticCloud*>(actorA);
				if (!cloud)
				{
					mcloud = dynamic_cast<AthleticMiniCloud*>(actorA);
					mcloudFlag = true;
				}
			}
			if (!player){ if(!mcloudFlag){if(!cloud)return; }
			else{ if(!mcloud)return;}}
			if (!mcloudFlag){if (player->GetTransform().pos.y < cloud->GetTransform().pos.y)return;}
			else{if (player->GetTransform().pos.y < mcloud->GetTransform().pos.y)return;}
			player->GetRigidBody().ClearGravity();
			player->GetRigidBody().SetVelocity(VGet(0, 40, 0));
		});
	EventManager::GetInstance().SetContactEventCallback(GameEventType::ATHLETIC_PLAYER_ON, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			AthleticPlayer* player1 = nullptr;
			AthleticPlayer* player2 = nullptr;
			player1 = dynamic_cast<AthleticPlayer*>(actorA);
			player2 = dynamic_cast<AthleticPlayer*>(actorB);
			if (!player1 || !player2)return;
			VECTOR pos1 = player1->GetTransform().pos;
			VECTOR pos2 = player2->GetTransform().pos;
			if (pos1.y > pos2.y)
			{
				player1->GetRigidBody().AddForce(VGet(0, 30, 0));
				player2->GetRigidBody().ClearGravity();
				player2->GetRigidBody().SetVelocity(VGet(0, 0, 0));
			}
			else
			{
				player2->GetRigidBody().AddForce(VGet(0, 30, 0));
				player1->GetRigidBody().ClearGravity();
				player1->GetRigidBody().SetVelocity(VGet(0, 0, 0));
			}
		});
	EventManager::GetInstance().SetContactEventCallback(GameEventType::ATHLETIC_FALL, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			AthleticPlayer* player = nullptr;
			AthleticFall* fall = nullptr;
			if (entityKindA == EntityKind::PLAYER) { player = dynamic_cast<AthleticPlayer*>(actorA); fall = dynamic_cast<AthleticFall*>(actorB); }
			if (entityKindB == EntityKind::PLAYER) { player = dynamic_cast<AthleticPlayer*>(actorB); fall = dynamic_cast<AthleticFall*>(actorA); }
			if (!player || !fall)return;
			player->SetCanInput(false);
		});
}

void Athletic::SetEventCallBack(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::FINISH, [this]()
		{

		});
}

void Athletic::LoadUI(void)
{
}

void Athletic::LoadSE(void)
{
}

void Athletic::InitUI(void)
{
}

void Athletic::InitSE(void)
{
}

void Athletic::InitCamera(void)
{
	SceneManager::GetInstance().GetCamera().ChangeMode(Camera::MODE::FREE);
	SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(76, 220 ,- 70));
	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(0.94f, 0.0f, 0.0f));
}

