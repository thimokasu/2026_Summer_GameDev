#include "ContainerBase.h"
#include"../../../Charactor/OneToFour/FeedJ/FeedJPlayer.h"
#include"../../../Stage/FeedJ/StationBase.h"
#include"../Food/FoodBase.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderSphere.h"

void ContainerBase::SubLoad(void)
{

}
void ContainerBase::SubInit(void)
{
	InitSlot();	
	foods_.resize(maxSlot_);
	trans_.pos.y = 100;
	entityKind_ = EntityKind::CONTAINER;
}
void ContainerBase::SubUpdate(void)
{
	if (player_)
	{
		auto f=player_->GetTransform().GetForward();
		auto yaw = atan2f(f.x, f.z);
		MATRIX pYaw = MGetRotY(yaw);
		auto offset = VTransform(localOffset_, pYaw);
		trans_.pos = VAdd(player_->GetTransform().pos, offset);
	}
	else if (station_)
	{
		trans_.pos = VAdd(station_->GetTransform().pos, localOffset_);
	}
}
void ContainerBase::SubDraw(void)
{

}
void ContainerBase::SubRelease(void)
{

}

bool ContainerBase::GetCanSetSlot(void)
{
	for (auto& slot : foods_)
	{
		if (slot.food_ == nullptr)
		{
			return true;
		}
	}
	return false;
}

void ContainerBase::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::SPHERE;
	info.layer_ = ColliderLayer::CONTAINER;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE,Layer::FOOD,Layer::STATION });
	float radius = 10.0f;
	std::unique_ptr<ColliderSphere>collider =
		std::make_unique<ColliderSphere>(info, radius, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void ContainerBase::InitRigidBody(void)
{
	rigidBody_.SetUseGravity(true);
}

void ContainerBase::AttachToPlayer(FeedJPlayer* player, VECTOR localOffset)
{
	player_ = player;
	localOffset_ = localOffset;
	for (auto& [shape, col]:ownColliders_)
	{
		col->SetActive(false);
	}
}
void ContainerBase::AttachToStation(StationBase* station, VECTOR localOffset)
{
	station_ = station;
	localOffset_ = localOffset;
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetActive(false);
	}
	rigidBody_.SetUseGravity(false);
	rigidBody_.SetVelocity(VGet(0, 0, 0));
}
void ContainerBase::Detach(void)
{
	if (player_)
	{
		player_ = nullptr;
	}
	if (station_)
	{
		station_ = nullptr;
	}
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetActive(true);
	}
	localOffset_ = VGet(0, 0, 0);
}

void ContainerBase::Cook(void)
{
	
}

void ContainerBase::SetSlot(std::vector<FoodBase*> foods)
{
	Slot slot;
	for (auto& f : foods)
	{
		slot.food_ = f;
		slot.kind = f->GetFoodKind();
	}
	foods_.push_back(slot);
}

void ContainerBase::SetSlot(FoodBase* food)
{
	Slot slot;
	slot.food_ = food;
	slot.kind = food->GetFoodKind();
	foods_.push_back(slot);
}

void ContainerBase::CrearHoldFood(void)
{
	for (auto& f : foods_)
	{
		f.food_ = nullptr;
	}
}



