#include "MarbleRace.h"
#include"../../../../Manager/Game/SceneManager.h"

#include"../../../../Object/Actor/Manager/ActorManager.h"

#include"../../../../Object/Actor/Camera/Camera.h"

#include"../../../../Object/Actor/Charactor/TwoPlay/MarbleRace/MarbleRacePlayer.h"
#include"../../../../Object/Actor/Charactor/TwoPlay/MarbleRace/State/MarbleRaveAttack.h"
#include"../../../../Object/Actor/Charactor/TwoPlay/MarbleRace/State/MarbleRaceHit.h"
#include"../../../../Object/Actor/Stage/MarbleRace/MarbleRaceGoal.h"
MarbleRace::MarbleRace(ActorManager* actMng, CollisionManager* colMng) :GameBase(actMng, colMng)
{
}

MarbleRace::~MarbleRace(void)
{
}

void MarbleRace::SubLoad(void)
{
}

void MarbleRace::SubInit(void)
{
	isUpdate_ = true;
}

void MarbleRace::SubUpdate(void)
{
}

void MarbleRace::SubDraw(void)
{
}

void MarbleRace::SubRelease(void)
{
}

void MarbleRace::SetContactEventRule(void)
{
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::PLAYER, GameEventType::PLAYER_HIT);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::MARBLE_GOAL, GameEventType::MARBLE_RACE_GOAL);
}

void MarbleRace::SetContactEventCallback(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::PLAYER_HIT, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			MarbleRacePlayer* player1;
			MarbleRacePlayer* player2;
			player1 = dynamic_cast<MarbleRacePlayer*>(actorA);
			player2 = dynamic_cast<MarbleRacePlayer*>(actorB);
			if (!player1 || !player2)return;
			if (player1->GetNowState<MarbleRaceAttack>()!=nullptr)
			{
				player2->ChangeState<MarbleRaceHit>();
			}
			else if (player2->GetNowState<MarbleRaceAttack>()!=nullptr)
			{
				player1->ChangeState<MarbleRaceHit>();
			}
		});

	EventManager::GetInstance().SetContactEventCallback(GameEventType::MARBLE_RACE_GOAL, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			MarbleRacePlayer* player=nullptr;
			MarbleRaceGoal* goal=nullptr;
			if (entityKindA == EntityKind::PLAYER) { player = dynamic_cast<MarbleRacePlayer*>(actorA); goal = dynamic_cast<MarbleRaceGoal*>(actorB); }
			if (entityKindB == EntityKind::PLAYER) { player = dynamic_cast<MarbleRacePlayer*>(actorB); goal = dynamic_cast<MarbleRaceGoal*>(actorA); }
			if (!player || !goal)return;
			clearPlayers_.push_back(player);
		});
}

void MarbleRace::SetEventCallBack(void)
{
}

void MarbleRace::LoadUI(void)
{
}

void MarbleRace::LoadSE(void)
{
}

void MarbleRace::InitUI(void)
{
}

void MarbleRace::InitSE(void)
{
}

void MarbleRace::InitCamera(void)
{
}
