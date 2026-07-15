#include "FeedJPlayer.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"State/FeedJStateHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"

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
	entityKind_ = EntityKind::PLAYER;
}

void FeedJPlayer::SubUpdate(void)
{
	CharactorBase::SubUpdate();
	if (!KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION).now&&!KEY::GetIns().GetInfo(KEY::KEY_TYPE::K_KEY_ACTION).now)isContactTrigger_ = false;
	if (!KEY::GetIns().GetInfo(KEY::KEY_TYPE::K_KEY_ACTION).now)isCook_ = false;
}

void FeedJPlayer::SubDraw(void)
{
	DrawFormatString(0, 10, 0xffffff, "State:%s", currentState_->GetName());
}

void FeedJPlayer::SubRelease(void)
{
}

void FeedJPlayer::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE,Layer::FOOD,Layer::STATION,Layer::CONTAINER});
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
	info.mask_ = ColliderBase::SetMask({ Layer::FOOD,Layer::STATION,Layer::CONTAINER });
	//info.isDraw_ = false;
	float radius2 = 10.0f;
	localPosTop = VGet(0.0f, 10.0f, 10.0f);
	localPosDown = VGet(0.0f, -10.0f, 10.0f);
	info.isTrigger_ = true;
	collider = std::make_unique<ColliderCapsule>(info, radius2, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void FeedJPlayer::CreateState(void)
{
	AddState(std::make_unique<FeedJ_IdleState>());
	AddState(std::make_unique<FeedJ_Cook>());
	AddState(std::make_unique<FeedJ_Walk>());
	AddState(std::make_unique<FeedJ_HoldWalk>());
	AddState(std::make_unique<FeedJ_HoldState>());
	AddState(std::make_unique<FeedJ_Dash>());
}

void FeedJPlayer::InitRigidBody(void)
{
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMoveSpeed(1);
	rigidBody_.SetMass(1000);
}
void FeedJPlayer::ActionInput(void)
{
}

void FeedJPlayer::ReturnToIdle(void)
{
	ChangeState<FeedJ_IdleState>();
}
