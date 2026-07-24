#include "MarbleRacePlayer.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"../../../Collider/ColliderSphere.h"
#include"State/MarbleRaceIdle.h"
#include"State/MarbleRaceMove.h"
#include"State/MarbleRaveAttack.h"
#include"State/MarbleRaceHit.h"
#include"../../../../../Manager/Resource/ResourceManager.h"
#include"../../../../../Utility/AsoUtility.h"
#include"../../../../Common/AnimationController.h"

MarbleRacePlayer::MarbleRacePlayer(void)
{
}

MarbleRacePlayer::~MarbleRacePlayer(void)
{
}

void MarbleRacePlayer::SubLoad(void)
{
	CharactorBase::SubLoad();
	if (playNumber_ == 0)
	{
		trans_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(SRC::FJ_PLAYER);
		float scale = 0.25f;
		trans_.scl = VGet(scale, scale, scale);
		trans_.quaRotLocal = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadD(180.0f), 0.0f));
		trans_.Update();
		//ÉAÉjÉÅÅ[ÉVÉáÉìÇÃìoò^
		animationController_ = std::make_unique<AnimationController>(trans_.modelId);
		animationController_->AddInFbx(0, 30.0f, 0);
		animationController_->AddInFbx(1, 60.0f, 1);
		animationController_->Add(2, 60.0f, "Data/Model/FindingJ/Player/PlayerAttack.mv1");
		animationController_->Play(1);
	}
	else {
		trans_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(SRC::RUNNER);
		float scale = 0.6f;
		trans_.scl = VGet(scale, scale, scale);		
		trans_.quaRotLocal = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadD(180.0f), 0.0f));
		trans_.Update();

		animationController_ = std::make_unique<AnimationController>(trans_.modelId);
		//animationController_->Add(0, 60.0f, "Data/Model/FindingJ/Runner/JazIdle.mv1");
		animationController_->Add(0, 6, "Data/Model/FindingJ/Runner/jazWalk.mv1");
		animationController_->Add(1, 10, "Data/Model/FindingJ/Runner/JazIdle.mv1");
		animationController_->Add(2, 60.0f, "Data/Model/FindingJ/Player/PlayerAttack.mv1");
		animationController_->Play(1);
	}


}

void MarbleRacePlayer::SubInit(void)
{
	CharactorBase::SubInit();
	entityKind_ = EntityKind::PLAYER;

}

void MarbleRacePlayer::SubUpdate(void)
{
	CharactorBase::SubUpdate();
}

void MarbleRacePlayer::SubDraw(void)
{
	DrawFormatString(0, 10, 0xffffff, "State:%s", currentState_->GetName());
}

void MarbleRacePlayer::SubRelease(void)
{
}

void MarbleRacePlayer::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMoveSpeed(1);
	rigidBody_.SetMass(10);
}

void MarbleRacePlayer::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	info.entityKind_ = EntityKind::PLAYER;
	info.localPos_.y = 100;
	float radius = 10.0f;
	VECTOR localPosTop = VGet(0.0f, 30.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, 10.0f, 0.0f);
	if (playNumber_ == 1)
	{
		localPosTop = VGet(0.0f, 50.0f, 0.0f);
		localPosDown = VGet(0.0f, 30.0f, 0.0f);
	}
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void MarbleRacePlayer::ReturnToIdle(void)
{
	ChangeState<MarbleRaceIdle>();
}

void MarbleRacePlayer::CreateState(void)
{
	AddState(std::make_unique<MarbleRaceIdle>());
	AddState(std::make_unique<MarbleRaceMove>());
	AddState(std::make_unique<MarbleRaceAttack>());
	AddState(std::make_unique<MarbleRaceHit>());
}

