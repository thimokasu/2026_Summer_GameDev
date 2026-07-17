#include "FeedJ.h"

#include"../../../../../Manager/Game/SceneManager.h"

#include"../../../../../Object/Actor/Manager/ActorManager.h"
		 
#include"../../../../../Object/Actor/Camera/Camera.h"

#include"../../../../../Object/Actor/Item/FeedJ/FeedJItemHeaders.h"
#include"../../../../../Object/Actor/Item/FeedJ/Food/FeedJ_Food_Headers.h"
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
	//カメラ座標
	DrawFormatString(0, 0, 0xffffff, "Camera Position: %f, %f, %f",
		SceneManager::GetInstance().GetCamera().GetPos().x,
		SceneManager::GetInstance().GetCamera().GetPos().y,
		SceneManager::GetInstance().GetCamera().GetPos().z);
	DrawFormatString(0, 20, 0xffffff, "Camera Angles: %f, %f, %f",
		SceneManager::GetInstance().GetCamera().GetAngles().x,
		SceneManager::GetInstance().GetCamera().GetAngles().y,
		SceneManager::GetInstance().GetCamera().GetAngles().z);
}

void FeedJ::SubRelease(void)
{
}

void FeedJ::SetContactEventRule(void)
{
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER_TRIGGER, EntityKind::FOOD, GameEventType::PLAYER_CONTACT_FOOD);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER_TRIGGER, EntityKind::CONTAINER, GameEventType::PLAYER_CONATCT_CONTAINER);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER_TRIGGER, EntityKind::STATION, GameEventType::PLAYER_CONTACT_STATION);
	EventManager::GetInstance().SetEventRule(EntityKind::FOOD, EntityKind::STATION, GameEventType::FOOD_STATION);
	EventManager::GetInstance().SetEventRule(EntityKind::FOOD, EntityKind::CONTAINER, GameEventType::FOOD_CONTAINER);
	EventManager::GetInstance().SetEventRule(EntityKind::CONTAINER, EntityKind::STATION, GameEventType::CONTAINER_STATION);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER_TRIGGER, EntityKind::STORAGE, GameEventType::PLAYER_CONTACT_STORAGE);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER_TRIGGER, EntityKind::TRASH, GameEventType::PLAYER_CONTACT_TRASH);
	
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
			if (entityKindA == EntityKind::PLAYER_TRIGGER) { player = dynamic_cast<FeedJPlayer*>(actorA); food = dynamic_cast<FoodBase*>(actorB); }
			else if (entityKindB == EntityKind::PLAYER_TRIGGER){ player = dynamic_cast<FeedJPlayer*>(actorB); food = dynamic_cast<FoodBase*>(actorA); }
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
			if (entityKindA == EntityKind::PLAYER_TRIGGER) { player = dynamic_cast<FeedJPlayer*>(actorA); container = dynamic_cast<ContainerBase*>(actorB); }
			if (entityKindB == EntityKind::PLAYER_TRIGGER) { player = dynamic_cast<FeedJPlayer*>(actorB); container = dynamic_cast<ContainerBase*>(actorA); }
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
			if (entityKindA == EntityKind::PLAYER_TRIGGER){	player = dynamic_cast<FeedJPlayer*>(actorA);station = dynamic_cast<StationBase*>(actorB);}
			else if (entityKindB == EntityKind::PLAYER_TRIGGER)	{player = dynamic_cast<FeedJPlayer*>(actorB);station = dynamic_cast<StationBase*>(actorA);}
			if (!player || !station)return;			//キャスト失敗
			if (rule.contactEvent_.type_ == ContactEventInfo::Type::BEGIN) {player->SetIsContact(true); }
			if (rule.contactEvent_.type_ == ContactEventInfo::Type::END) {player->SetIsContact(false); }
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
						int idx=contaier->GetEmptySlotIndex();
						if (idx == -1)return;
						contaier->SetSlot(f, idx);
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
							int idx = contaier->GetEmptySlotIndex();
							if (idx == -1)return;
							contaier->SetSlot(f, idx);
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
					else if (auto food = dynamic_cast<FoodBase*>(player->GetHoldItem()))
					{
						if (!station->GetHoldItem())
						{
							station->SetHoldItem(food);
							food->AttachToStation(station, VGet(0, 5, 0));
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
					auto container = dynamic_cast<ContainerBase*>(station->GetHoldItem());
					if (!container)return;				//ステーションにコンテナがない場合
					if (!container->GetCanCook())return;		//調理用コンテナのみ
					auto food = container->GetHoldFood();
					if (!food)return;					//食材がない場合
					if (!food->GetCanCook())return;		//食材がすでに調理済みの場合
					food->ChangeState<FeedJ_Food_Cooking>();
					player->ChangeState<FeedJ_Cook>();
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
							if (!container->GetCanPickUp())return;
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
#pragma region player:storage
		EventManager::GetInstance().SetContactEventCallback(GameEventType::PLAYER_CONTACT_STORAGE, [this](const ContactRule& rule)
			{
				auto entityKindA = rule.contactEvent_.entityA.entityKind_;
				auto entityKindB = rule.contactEvent_.entityB.entityKind_;
				auto idA = rule.contactEvent_.entityA.entityID_;
				auto idB = rule.contactEvent_.entityB.entityID_;
				auto actorA = actorMng_->FindActorByID(idA);
				auto actorB = actorMng_->FindActorByID(idB);
				FeedJPlayer* player = nullptr;
				StorageBase* storage = nullptr;
				if (entityKindA == EntityKind::PLAYER_TRIGGER){player = dynamic_cast<FeedJPlayer*>(actorA);	storage = dynamic_cast<StorageBase*>(actorB);}
				else if (entityKindB == EntityKind::PLAYER_TRIGGER){player = dynamic_cast<FeedJPlayer*>(actorB);storage = dynamic_cast<StorageBase*>(actorA);}
				if (!player || !storage)return;
				if (!player->GetContactTrigger())return;
				if (player->GetHoldItem())return;//アイテムを保持している場合何もしない
				auto f=storage->CreateFood();
				f->AttachToPlayer(player);
				player->SetHoldItem(dynamic_cast<ItemBase*>(f.get()));
				player->ChangeState<FeedJ_HoldState>();
				actorMng_->AddActor(std::move(f),this);
			});
#pragma endregion
#pragma region player:trash
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
			if (rule.contactEvent_.type_ != ContactEventInfo::Type::BEGIN)return;
			//ステーションが埋まってる
			if (auto hold=station->GetHoldItem())
			{
				//ステーションがコンテナを保持している
				if (auto container = dynamic_cast<ContainerBase*>(hold))
				{
					int idx = container->GetEmptySlotIndex();
					if (idx == -1)return;
					auto food = dynamic_cast<FoodBase*>(item);
					container->SetSlot(food,idx);
					food->AttachToContainer(container, VGet(0, 5, 0));
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
			int idx = container->GetEmptySlotIndex();
			if (idx == -1)return;
			container->SetSlot(food, idx);
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
	SceneManager::GetInstance().GetCamera().SetCameraPos({ 120,170,20 });
	SceneManager::GetInstance().GetCamera().SetCameraAngles({ 1.3,0,0 });
}
