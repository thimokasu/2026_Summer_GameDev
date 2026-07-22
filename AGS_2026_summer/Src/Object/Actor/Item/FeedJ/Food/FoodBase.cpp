#include "FoodBase.h"
#include"../../../Charactor/OneToFour/FeedJ/FeedJPlayer.h"
#include"../../../Stage/FeedJ/StationBase.h"
#include"../Container/ContainerBase.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"State/FeedJ_Food_Cooked.h"
#include"State/FeedJ_Food_Idle.h"
#include"State/FeedJ_Food_Cooking.h"
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
	AddState(std::make_unique<FeedJ_Food_Idle>());
	AddState(std::make_unique < FeedJ_Food_Cooked>());
	AddState(std::make_unique<FeedJ_Food_Cooking>());
	ChangeState<FeedJ_Food_Idle>();

}

void FoodBase::SubUpdate(void)
{

	if (currentState_)
	{
		currentState_->Update(this);
	}

	
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
	else
	{
		ChangeState<FeedJ_Food_Idle>();
	}
}

void FoodBase::SubDraw(void)
{
	DrawFormatString(0, 30, 0xffffff, "%d", cookTime_);
	DrawCookTime();
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
	info.entityKind_ = EntityKind::FOOD;
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
	trans_.pos = VAdd(pos, VScale(forward, 5));
	trans_.pos.y = 25;
	rigidBody_.SetVelocity(VGet(0, 0, 0));
	rigidBody_.AddForce(VScale(forward, 20));
	rigidBody_.SetUseGravity(true);
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetActive(true);
	}
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
	for (auto& [shape, col] : ownColliders_)
	{
		col->SetActive(true);
	}
}

void FoodBase::DrawCookTime(void)
{
	// 調理中でなければ描画しない（あるいはIdleで非表示にするなど必要に応じて調整）
	// 例: cookTime_ が 0 より大きく、COOKING_TIME 未満の場合のみ表示
	if (cookTime_ <= 0 || cookTime_ >= COOKING_TIME) {
		return;
	}

	// 1. 進行度（0.0f ～ 1.0f）を計算
	float rate = static_cast<float>(cookTime_) / static_cast<float>(COOKING_TIME);
	if (rate > 1.0f) rate = 1.0f;

	// 2. 画面上の描画位置を決定する
	// 【パターンA】ワールド座標（3D空間の食材の位置）からスクリーン座標に変換する場合（DxLibの例）
	VECTOR screenPos = ConvWorldPosToScreenPos(trans_.pos);

	// カメラの裏側に入っている場合は描画しない
	if (screenPos.z < 0.0f || screenPos.z > 1.0f) {
		return;
	}

	int barWidth = 50;   // ゲージの横幅
	int barHeight = 10;   // ゲージの縦幅
	int x = static_cast<int>(screenPos.x) - barWidth / 2;
	int y = static_cast<int>(screenPos.y) - 60; // 食材の少し上に表示

	// 【パターンB】画面固定で表示したい場合は、固定の座標を指定してください
	// int x = 100;
	// int y = 100;

	// 3. ゲージの背景（枠・背景色）を描画
	DrawBox(x, y, x + barWidth, y + barHeight, GetColor(50, 50, 50), TRUE); // 背景
	DrawBox(x, y, x + barWidth, y + barHeight, GetColor(255, 255, 255), FALSE); // 外枠

	// 4. 進行状況に応じたバー（中身）を描画
	int innerWidth = static_cast<int>((barWidth - 2) * rate);
	if (innerWidth > 0) {
		// 調理が進むにつれて色を変える（例: 赤から緑、または黄色など）
		unsigned int gaugeColor = GetColor(255, 200, 0); // 黄色・オレンジ系
		DrawBox(x + 1, y + 1, x + 1 + innerWidth, y + barHeight - 1, gaugeColor, TRUE);
	}
}