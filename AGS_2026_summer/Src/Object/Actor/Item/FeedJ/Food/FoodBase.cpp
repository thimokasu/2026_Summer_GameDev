#include "FoodBase.h"
#include"../../../Charactor/OneToFour/FeedJ/FeedJPlayer.h"
#include"../../../Stage/FeedJ/StationBase.h"
#include"../Container/ContainerBase.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"State/FeedJ_Food_Cooked.h"
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
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetUseRotation(true);
}

void FoodBase::SubUpdate(void)
{
	if (player_ != nullptr)isDraw_ = false;
	if (station_)
	{
		trans_.pos = VAdd(station_->GetTransform().pos, localOffset_);
	}
	else if (container_)
	{
		trans_.pos = VAdd(container_->GetTransform().pos, localOffset_);
	}
	if (cookTime_ >= COOKING_TIME)
	{
		ChangeState<FeedJ_Food_Cooked>();
	}
}

void FoodBase::SubDraw(void)
{
}

void FoodBase::SubRelease(void)
{
}

void FoodBase::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::FOOD;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE,Layer::STATION,Layer::FOOD,Layer::CONTAINER });
	float radius = 6.0f;
	VECTOR localPosTop = VGet(0.0f, 2.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, -2.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

}

void FoodBase::Throw(ActorBase* target)
{
	auto& pos = target->GetTransform().pos;
	auto forward = target->GetTransform().GetForward();
	trans_.pos = VAdd(pos, VScale(forward, 15));
	trans_.pos.y = 30;
	rigidBody_.SetVelocity(VGet(0, 0, 0));
	rigidBody_.AddForce(VScale(forward, 30));
	rigidBody_.SetUseGravity(true);
}

void FoodBase::OnCook(void)
{
}



void FoodBase::AttachToPlayer(FeedJPlayer* player)
{
	Detach();
	player_ = player;
	for (auto& [shape,col] : ownColliders_)
	{
		col->SetActive(false);
	}
}

void FoodBase::AttachToContainer(ContainerBase* container, VECTOR localOffset)
{
	Detach();
	container_ = container;
	localOffset_ = localOffset;
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetActive(false);
	}
	rigidBody_.SetUseGravity(false);
	rigidBody_.SetVelocity(VGet(0, 0, 0));
}

void FoodBase::AttachToStation(StationBase* station, VECTOR localOffset)
{
	Detach();
	station_ = station;
	localOffset_ = localOffset;	
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetActive(false);
	}
	rigidBody_.SetUseGravity(false);
	rigidBody_.SetVelocity(VGet(0, 0, 0));
}

void FoodBase::Detach(void)
{
	if(player_ != nullptr)
	{
		player_ = nullptr;
		isDraw_ = true;
	}
	if (station_ != nullptr)
	{
		station_ = nullptr;
	}
	if(container_ != nullptr)
	{
		container_ = nullptr;
	}
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetActive(true);
	}
	localOffset_ = VGet(0, 0, 0);
}

void FoodBase::Drop( ActorBase* target)
{
	auto& pos = target->GetTransform().pos;
	auto forward = target->GetTransform().GetForward();
	trans_.pos = VAdd(pos, VScale(forward, 15));
	trans_.pos.y = 30;
	rigidBody_.SetVelocity(VGet(0, 0, 0));
	rigidBody_.SetUseGravity(true);
}

void FoodBase::DrawCookTime(void)
{
}
