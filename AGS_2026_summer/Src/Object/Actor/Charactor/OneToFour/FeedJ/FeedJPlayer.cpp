#include "FeedJPlayer.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"State/FeedJStateHeaders.h"

FeedJPlayer::FeedJPlayer(void)
{
}

FeedJPlayer::~FeedJPlayer(void)
{
}

void FeedJPlayer::SubLoad(void)
{
	CharactorBase::SubLoad();
}

void FeedJPlayer::SubInit(void)
{
	CharactorBase::SubInit();
}

void FeedJPlayer::SubUpdate(void)
{
	CharactorBase::SubUpdate();
}

void FeedJPlayer::SubDraw(void)
{
}

void FeedJPlayer::SubRelease(void)
{
}

void FeedJPlayer::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	float radius = 10.0f;
	VECTOR localPosTop = VGet(0.0f, 10.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, -10.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

	//プレイヤーのアイテム、ステージコンタクト用コライダー
	//プレイヤーの正面より少し前に配置
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR_TRIGGER;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	float radius2 = 10.0f;
	localPosTop = VGet(0.0f, 10.0f, 10.0f);
	localPosDown = VGet(0.0f, -10.0f, 10.0f);
	info.isTrigger_ = true;
	collider = std::make_unique<ColliderCapsule>(info, radius2, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}
void FeedJPlayer::InitRigidBody(void)
{
	rigidBody_.SetUseGravity(true);
}
void FeedJPlayer::ActionInput(void)
{
}

void FeedJPlayer::ReturnToIdle(void)
{
	ChangeState<FeedJ_IdleState>();
}
