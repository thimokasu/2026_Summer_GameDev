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
	EventManager::GetInstance().SetEventRule(EntityKind::FOOD, EntityKind::STATION, GameEventType::FOOD_STATION);
	EventManager::GetInstance().SetEventRule(EntityKind::FOOD, EntityKind::CONTAINER, GameEventType::FOOD_CONTAINER);
	EventManager::GetInstance().SetEventRule(EntityKind::CONTAINER, EntityKind::STATION, GameEventType::CONTAINER_STATION);
}

void FeedJ::SetContactEventCallback(void)
{
#pragma region player:food
	EventManager::GetInstance().SetContactEventCallback(GameEventType::PLAYER_CONTACT_FOOD, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			FoodBase* food = nullptr;
			FeedJPlayer* player = nullptr;
			if (entityKindA == EntityKind::PLAYER) { player = dynamic_cast<FeedJPlayer*>(actorA); food = dynamic_cast<FoodBase*>(actorB); }
			else if (entityKindB == EntityKind::PLAYER){ player = dynamic_cast<FeedJPlayer*>(actorB); food = dynamic_cast<FoodBase*>(actorA); }
			if (!player || !food)return;
			if (rule.contactEvent_.type_ == ContactEventInfo::Type::BEGIN) { player->SetIsContact(true); }
			if (rule.contactEvent_.type_ == ContactEventInfo::Type::END) { player->SetIsContact(false); }
			if (!player->GetContactTrigger())return;	//トリガーがオフ
			if (player->GetHoldItem())return;			//アイテムを所持している
			//プレイヤーに食材をアタッチする
			player->SetHoldItem(food);
			player->ChangeState<FeedJ_HoldState>();
			food->AttachToPlayer(player);
		}
	);
#pragma endregion
#pragma region player:contaier
	EventManager::GetInstance().SetContactEventCallback(GameEventType::PLAYER_CONATCT_CONTAINER, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			FeedJPlayer* player = nullptr;
			ContainerBase* container = nullptr;
			if (entityKindA == EntityKind::PLAYER) { player = dynamic_cast<FeedJPlayer*>(actorA); container = dynamic_cast<ContainerBase*>(actorB); }
			if (entityKindB == EntityKind::PLAYER) { player = dynamic_cast<FeedJPlayer*>(actorB); container = dynamic_cast<ContainerBase*>(actorA); }
			if (!player || !container)return;
			if (rule.contactEvent_.type_ == ContactEventInfo::Type::BEGIN) { player->SetIsContact(true); }
			if (rule.contactEvent_.type_ == ContactEventInfo::Type::END) { player->SetIsContact(false); }
			if (!player->GetContactTrigger())return;
			if (player->GetHoldItem())return;
			if (container->GetIsAttachStation())return;
			player->SetHoldItem(container);
			player->ChangeState<FeedJ_HoldState>();
			container->AttachToPlayer(player, VGet(0, 0, 20));
		});
#pragma endregion
#pragma region player:station
	EventManager::GetInstance().SetContactEventCallback(GameEventType::PLAYER_CONTACT_STATION, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			FeedJPlayer* player = nullptr;
			StationBase* station = nullptr;
			if (entityKindA == EntityKind::PLAYER)
			{
				player = dynamic_cast<FeedJPlayer*>(actorA);
				station = dynamic_cast<StationBase*>(actorB);
			}
			else if (entityKindB == EntityKind::PLAYER)
			{
				player = dynamic_cast<FeedJPlayer*>(actorB);
				station = dynamic_cast<StationBase*>(actorA);
			}
			if (!player || !station)return;			//キャスト失敗
			if (rule.contactEvent_.type_ == ContactEventInfo::Type::BEGIN) { player->SetIsContact(true); }
			if (rule.contactEvent_.type_ == ContactEventInfo::Type::END) { player->SetIsContact(false); }
			if (!player->GetContactTrigger())return;	//トリガーオフ
			//プレイヤーがアイテムを所持している
			if (player->GetHoldItem()) {
				//ステーションがコンテナを保持している
				if (auto contaier = dynamic_cast<ContainerBase*>(station->GetHoldItem()))
				{
					//プレイヤーが食材を所持している
					if (auto f = dynamic_cast<FoodBase*>(player->GetHoldItem()))
					{
						player->ReleaseHoldItem();
						player->ChangeState<FeedJ_IdleState>();
						contaier->SetSlot(f);
						f->AttachToContainer(contaier, VGet(0, 5, 0));
					}
				}
				//ステーションがコンテナーを保持していない
				else
				{
					//プレイヤーがコンテナを所持している
					if (auto container = dynamic_cast<ContainerBase*>(player->GetHoldItem()))
					{
						//ステーションが食材を所持している場合
						if (auto f = dynamic_cast<FoodBase*>(station->GetHoldItem()))
						{
							container->Detach();
							f->AttachToContainer(container, VGet(0, 5, 0));
							container->AttachToStation(station, VGet(0, 10, 0));
							container->SetIsAttachStation(true);
							contaier->SetSlot(f);
							station->SetHoldItem(container);
							player->ReleaseHoldItem();
							player->ChangeState<FeedJ_IdleState>();
						}
						//ステーションが何も所持していない場合
						else if (!station->GetHoldItem())
						{
							container->Detach();
							container->AttachToStation(station, VGet(0, 10, 0));
							container->SetIsAttachStation(true);
							station->SetHoldItem(container);
							player->ReleaseHoldItem();
							player->ChangeState<FeedJ_IdleState>();
						}
					}
				}
			}
			//アイテムを未所持
			else
			{
				//調理フラグがONの場合
				if (player->GetIsCook())
				{

				}
				else
				{
					//ステーションがアイテムを所持している場合
					//プレイヤーにアタッチする
					if (auto item = station->GetHoldItem())
					{
						if (auto food = dynamic_cast<FoodBase*>(item))
						{
							food->Detach();
							food->AttachToPlayer(player);
						}
						else if (auto container = dynamic_cast<ContainerBase*>(item))
						{
							container->Detach();
							container->AttachToPlayer(player, VGet(0, 0, 20));
							container->SetIsAttachStation(false);
						}
						station->ReleaseHoldItem();
						player->SetHoldItem(item);
						player->ChangeState<FeedJ_HoldState>();
					}
				}
			}
		});
#pragma endregion
#pragma region food:station
	EventManager::GetInstance().SetContactEventCallback(GameEventType::FOOD_STATION, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			ItemBase* item = nullptr;
			StationBase* station = nullptr;
			if (entityKindA == EntityKind::FOOD){item = dynamic_cast<ItemBase*>(actorA);station = dynamic_cast<StationBase*>(actorB);}
			else if (entityKindB == EntityKind::FOOD){item = dynamic_cast<ItemBase*>(actorB);station = dynamic_cast<StationBase*>(actorA);}
			if (!item || !station)return;		//キャスト失敗
			//ステーションが埋まってる
			if (auto hold=station->GetHoldItem())
			{
				//ステーションがコンテナを保持している
				if (auto container = dynamic_cast<ContainerBase*>(hold))
				{
					if (container->GetCanSetSlot())
					{
						auto food = dynamic_cast<FoodBase*>(item);
						container->SetSlot(food);
						food->AttachToContainer(container, VGet(0, 5, 0));
					}
				}
			}
			else
			{
				//ステーションにアイテムをアタッチ
				station->SetHoldItem(item);
				if (auto food = dynamic_cast<FoodBase*>(item))
				{
					food->AttachToStation(station, VGet(0, 10, 0));
				}
			}
		});
#pragma endregion
#pragma region food:container
	EventManager::GetInstance().SetContactEventCallback(GameEventType::FOOD_CONTAINER, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			FoodBase* food = nullptr;
			ContainerBase* container = nullptr;
			if (entityKindA == EntityKind::FOOD) { food = dynamic_cast<FoodBase*>(actorA); container = dynamic_cast<ContainerBase*>(actorB); }
			else if (entityKindB == EntityKind::FOOD) { food = dynamic_cast<FoodBase*>(actorB); container = dynamic_cast<ContainerBase*>(actorA); }
			if (!food || !container)return;
			if (!container->GetCanSetSlot())return;
			container->SetSlot(food);
			food->AttachToContainer(container, VGet(0, 5, 0));
		});
#pragma endregion
#pragma region container:station
	EventManager::GetInstance().SetContactEventCallback(GameEventType::CONTAINER_STATION, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			ContainerBase* container = nullptr;
			StationBase* station = nullptr;
			if (entityKindA == EntityKind::CONTAINER) { container = dynamic_cast<ContainerBase*>(actorA); station = dynamic_cast<StationBase*>(actorB); }
			else if (entityKindB == EntityKind::CONTAINER) { container = dynamic_cast<ContainerBase*>(actorB); station = dynamic_cast<StationBase*>(actorA); }
			if (!container || !station)return;
			if (station->GetHoldItem())return;
			container->AttachToStation(station, VGet(0, 10, 0));
			station->SetHoldItem(container);
		});
#pragma endregion
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
