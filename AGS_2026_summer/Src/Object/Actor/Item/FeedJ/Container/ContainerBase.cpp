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
	foods_.resize(maxSlot_);
	entityKind_ = EntityKind::CONTAINER;
	InitSlot();	
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

// 空いているスロットのインデックスを返す
// 空きがなければ -1 を返す
int ContainerBase::GetEmptySlotIndex(void)
{
	for (int i = 0; i < (int)foods_.size(); ++i)
	{
		if (foods_[i].food_ == nullptr)
		{
			return i; // 最初の空きインデックスを返す
		}
	}
	return -1; // 空きなし
}

void ContainerBase::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::SPHERE;
	info.layer_ = ColliderLayer::CONTAINER;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE,Layer::FOOD,Layer::STATION });
	info.entityKind_ = EntityKind::CONTAINER;
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

void ContainerBase::SetSlot(FoodBase* food, int idx)
{
	Slot slot;
	slot.food_ = food;
	slot.kind = food->GetFoodKind();
	foods_[idx] = slot;
}

void ContainerBase::CrearHoldFood(void)
{
	for (auto& f : foods_)
	{
		f.food_ = nullptr;
	}
}



