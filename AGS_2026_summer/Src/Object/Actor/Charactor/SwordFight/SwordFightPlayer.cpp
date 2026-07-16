#include "SwordFightPlayer.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderCapsule.h"
#include"SwordState/SwordFIghtStateHeaders.h"
#include"../../../../Manager/Generic/KeyManager.h"
#include "../../../Common/AnimationController.h"
#include"../../../../Utility/AsoUtility.h"
#include "../../../../Application.h"


SwordFightPlayer::SwordFightPlayer(void)
{
}

SwordFightPlayer::~SwordFightPlayer(void)
{
}

void SwordFightPlayer::SubLoad(void)
{
	CharactorBase::SubLoad();
	trans_.modelId = MV1LoadModel("Data/Model/Player/Block React Large.mv1");
	trans_.modelId = MV1LoadModel("Data/Model/Player/DamageReact Large From Left.mv1");
	trans_.modelId = MV1LoadModel("Data/Model/Player/Lose.mv1");
	trans_.modelId = MV1LoadModel("Data/Model/Player/Player Attack.mv1");
	trans_.modelId = MV1LoadModel("Data/Model/Player/Player Idle.mv1");
	trans_.modelId = MV1LoadModel("Data/Model/Player/Player_T.mv1");
	trans_.modelId = MV1LoadModel("Data/Model/Player/Great Sword Walk.mv1");
}

void SwordFightPlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	trans_.quaRotLocal = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadD(180.0f), 0.0f));

	//ÉAÉjÉÅÅ[ÉVÉáÉìÇÃìoò^
	std::string path = Application::PATH_MODEL + "Player/";

	animationController_ = std::make_unique<AnimationController>(trans_.modelId);
	animationController_->Add((int)animType::Idle, 20.0f,path+"Player Idle.mv1");
	animationController_->Add((int)animType::Walk, 20.0f, path + "Great Sword Walk.mv1");
	animationController_->Add((int)animType::Attack, 20.0f, path + "Player Attack.mv1");
	animationController_->Add((int)animType::Damage, 20.0f, path + "DamageReact Large From Left.mv1");
	animationController_->Add((int)animType::Block, 20.0f, path + "Block React Large.mv1");

	CharactorBase::SubInit();
}

void SwordFightPlayer::SubUpdate(void)
{
	CharactorBase::SubUpdate();
	if (!KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION).now)isContactTrigger_ = false;
}

void SwordFightPlayer::SubDraw(void)
{
	MV1DrawModel(trans_.modelId);

	DrawFormatString(0, 10, 0xffffff, "State:%s", currentState_->GetName());
}

void SwordFightPlayer::SubRelease(void)
{
}

void SwordFightPlayer::InitCollider(void)
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
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR_TRIGGER;
	info.mask_ = ColliderBase::SetMask({ Layer::SOWRD,Layer::CPU });
	float radius2 = 10.0f;
	localPosTop = VGet(0.0f, 10.0f, 10.0f);
	localPosDown = VGet(0.0f, -10.0f, 10.0f);
	info.isTrigger_ = true;
	collider = std::make_unique<ColliderCapsule>(info, radius2, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void SwordFightPlayer::CreateState(void)
{
	AddState(std::make_unique<SwordFight_Idle>());
	AddState(std::make_unique<SwordFight_Block>());
	AddState(std::make_unique<SwordFIght_Walk>());
	AddState(std::make_unique<SwordFight_Lose>());
	AddState(std::make_unique<SwordFight_Damage>());
	AddState(std::make_unique<SwordFight_Attack>());
}

void SwordFightPlayer::InitRigidBody(void)
{
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMoveSpeed(1);
}

void SwordFightPlayer::ActionInput(void)
{

}

void SwordFightPlayer::ReturnToIdle(void)
{
	ChangeState<SwordFight_Idle>();
}



