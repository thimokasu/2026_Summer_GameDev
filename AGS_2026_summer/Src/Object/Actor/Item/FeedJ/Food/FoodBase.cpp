#include "FoodBase.h"
#include"../../../Charactor/OneToFour/FeedJ/FeedJPlayer.h"
#include"../../../Stage/FeedJ/StationBase.h"
#include"../Container/ContainerBase.h"

FoodBase::FoodBase(void)
{
}

FoodBase::~FoodBase(void)
{
}

void FoodBase::SubLoad(void)
{
}

void FoodBase::SubInit(void)
{
}

void FoodBase::SubUpdate(void)
{
	if (player_ != nullptr)isDraw_ = false;
}

void FoodBase::SubDraw(void)
{
}

void FoodBase::SubRelease(void)
{
}

void FoodBase::InitCollider(void)
{
}

void FoodBase::PlaceItem(ActorBase* owner)
{
}

void FoodBase::Throw(ActorBase* owner)
{
}

void FoodBase::OnCook(void)
{
}

void FoodBase::AttachToPlayer(FeedJPlayer* player)
{
	player_ = player;
}

void FoodBase::AttachToContainer(ContainerBase* container, VECTOR localOffset)
{
	container_ = container;
	localOffset_ = localOffset;
}

void FoodBase::AttachToStation(StationBase* station, VECTOR localOffset)
{
	station_ = station;
	localOffset_ = localOffset;
}

void FoodBase::Detach(void)
{
	if(player_ != nullptr)
	{
		player_ = nullptr;
	}
	if (station_ != nullptr)
	{
		station_ = nullptr;
	}
	if(container_ != nullptr)
	{
		container_ = nullptr;
	}
}

void FoodBase::Drop( ActorBase* target)
{
	auto& pos = target->GetTransform().pos;
	auto forward = target->GetTransform().GetForward();
}

void FoodBase::DrawCookTime(void)
{
}
