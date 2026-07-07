#include "FeedJ.h"

#include"../../../../../Manager/Game/SceneManager.h"

#include"../../../../../Object/Actor/Manager/ActorManager.h"
		 
#include"../../../../../Object/Actor/Camera/Camera.h"

#include"../../../../../Object/Actor/Item/FeedJ/FeedJItemHeaders.h"
#include"../../../../../Object/Actor/Stage/FeedJ/FeedJStageHeaders.h"
#include"../../../../../Object/Actor/Charactor/OneToFour/FeedJ/FeedJPlayer.h"

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
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER_CONTACT_TRIGGER, EntityKind::FOOD, GameEventType::PLAYER_TRIGGER_CONTACT_FOOD);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER_CONTACT_TRIGGER, EntityKind::PLAYER_CONTACT_TRIGGER, GameEventType::PLAYER_TRIGGER_CONATCT_CONTAINER);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER_CONTACT_TRIGGER, EntityKind::STATION, GameEventType::PLAYER_TRIGGER_CONTACT_STATION);
}

void FeedJ::SetContactEventCallback(void)
{
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
