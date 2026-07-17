#include "SpikeDropPlayer.h"
#include<DxLib.h>
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../../../Manager/Game/UIManager.h"
#include"../../../../../Manager/Resource/ResourceManager.h"
#include"../../../../../Manager/System/EventSystem/EventManager.h"
#include"../../../Camera/Camera.h"

#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"../../../Collider/ColliderSphere.h"

#include"State/SpikeDropPlayerHeaders.h"

SpikeDropPlayer::SpikeDropPlayer(void)
{
}

SpikeDropPlayer::~SpikeDropPlayer(void)
{
}

void SpikeDropPlayer::SubLoad(void)
{
	CharactorBase::SubLoad();
}

void SpikeDropPlayer::SubInit(void)
{
	CharactorBase::SubInit();
	entityKind_ = EntityKind::PLAYER;
	ChangeState<SpikeDropPlayerIdle>();
}

void SpikeDropPlayer::SubUpdate(void)
{
	CharactorBase::SubUpdate();
}

void SpikeDropPlayer::SubDraw(void)
{
}

void SpikeDropPlayer::SubRelease(void)
{
}

void SpikeDropPlayer::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE,Layer::ACTOR_TRIGGER });
	info.entityKind_ = EntityKind::PLAYER;
	float radius = 4.0f;
	VECTOR localPosTop = VGet(0.0f, 10.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, -10.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

	//他プレイヤーから踏まれるための頭用センサーコライダー
	info.shape_ = ColliderShape::SPHERE;
	info.layer_ = ColliderLayer::ACTOR_TRIGGER;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::PLAYER_TRIGGER;
	radius = 4.0f;
	info.localPos_ = VGet(0, 20, 0);
	info.isTrigger_ = true;
	info.debugColor_ = GetColor(0, 255, 0);
	std::unique_ptr<ColliderSphere> collider2 = std::make_unique<ColliderSphere>(info, radius, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider2));
}

void SpikeDropPlayer::InitRigidBody(void)
{
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetMoveSpeed(1);
	rigidBody_.SetJumpForce(25);
	rigidBody_.SetMass(1);
}

void SpikeDropPlayer::ReturnToIdle(void)
{
	ChangeState<SpikeDropPlayerIdle>();
}

void SpikeDropPlayer::CreateState(void)
{
	AddState(std::make_unique<SpikeDropPlayerHit>());
	AddState(std::make_unique<SpikeDropPlayerIdle>());
	AddState(std::make_unique<SpikeDropPlayerJump>());
	AddState(std::make_unique<SpikeDropPlayerMove>());
	AddState(std::make_unique<SpikeDropPlayerStepedOn>());
}
