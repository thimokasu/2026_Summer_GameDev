#include "FeedJ.h"

#include"../../../../../Manager/Game/SceneManager.h"

#include"../../../../../Object/Actor/Manager/ActorManager.h"
		 
#include"../../../../../Object/Actor/Camera/Camera.h"

#include"../../../../../Object/Actor/Item/FeedJ/FeedJItemHeaders.h"
#include"../../../../../Object/Actor/Stage/FeedJ/FeedJStageHeaders.h"
#include"../../../../../Object/Actor/Charactor/OneToFour/FeedJ/FeedJPlayer.h"
#include"../../../../../Object/Actor/Charactor/OneToFour/FeedJ/State/FeedJStateHeaders.h"

FeedJ::FeedJ(ActorManager* actMng, CollisionManager* colMng)
	:GameBase(actMng, colMng)
{
}

FeedJ::~FeedJ(void)
{
}

void FeedJ::SubLoad(void)
{
}

void FeedJ::SubInit(void)
{
	isUpdate_ = true;
}

void FeedJ::SubUpdate(void)
{
}

void FeedJ::SubDraw(void)
{
}

void FeedJ::SubRelease(void)
{
}

void FeedJ::SetContactEventRule(void)
{
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::FOOD, GameEventType::PLAYER_CONTACT_FOOD);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::CONTAINER, GameEventType::PLAYER_CONATCT_CONTAINER);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::STATION, GameEventType::PLAYER_CONTACT_STATION);
}

void FeedJ::SetContactEventCallback(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::PLAYER_CONTACT_FOOD, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
				auto idA = rule.contactEvent_.entityA.entityID_;
				auto idB = rule.contactEvent_.entityB.entityID_;
				auto actorA = actorMng_->FindActorByID(idA);
				auto actorB = actorMng_->FindActorByID(idB);
			if (entityKindA == EntityKind::PLAYER)
			{
				auto& player = dynamic_cast<FeedJPlayer&>(*actorA);
				if (player.GetContactTrigger())
				{
					auto& item = dynamic_cast<ItemBase&>(*actorB);
					player.SetHoldItem(&item);
					player.ChangeState<FeedJ_HoldState>();
					auto& food = dynamic_cast<FoodBase&>(item);
					food.AttachToPlayer(&player);
				}
			}
			else if(entityKindB==EntityKind::PLAYER)
			{
				auto& player = dynamic_cast<FeedJPlayer&>(*actorB);
				if (player.GetContactTrigger())
				{
					auto& item = dynamic_cast<ItemBase&>(*actorA);
					player.SetHoldItem(&item);
					player.ChangeState<FeedJ_HoldState>();
					auto& food = dynamic_cast<FoodBase&>(item);
					food.AttachToPlayer(&player);
				}
			}
		}
	);
}


void FeedJ::SetEventCallBack(void)
{
}

void FeedJ::LoadUI(void)
{
}

void FeedJ::LoadSE(void)
{
}

void FeedJ::InitUI(void)
{
}

void FeedJ::InitSE(void)
{
}

void FeedJ::InitCamera(void)
{
}
