#include "SwordFIghtCPU.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"SwordFIghtCPUHeaders.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include "../../../../Common/AnimationController.h"
#include"../../../../../Utility/AsoUtility.h"
#include "../../../../../Application.h"


SwordFIghtCPU::SwordFIghtCPU(void)
{
}

SwordFIghtCPU::~SwordFIghtCPU(void)
{
}

void SwordFIghtCPU::SubLoad(void)
{
	CharactorBase::SubLoad();
	trans_.modelId = MV1LoadModel("Data/Model/CPU/Great Sword Idle CPU.mv1");
	Swordtrans_.modelId = MV1LoadModel("Data/Model/Player/SwordRed.mv1");
}

void SwordFIghtCPU::SubInit(void)
{
	entityKind_ = EntityKind::CPU;
	trans_.quaRotLocal = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadD(180.0f), 0.0f));
	trans_.pos = VGet(0, 100.0f, 400.0f);


	Swordtrans_.scl.x = 3.0f;
	Swordtrans_.scl.z = 2.5f;
	Swordtrans_.scl.y = 3.5f;

	Swordtrans_.quaRotLocal =
		Quaternion::Euler(
			VGet(
				0.0f,
				0.0f,
				AsoUtility::Deg2RadD(-45.0f)
			)
		);
	Swordtrans_.Update();

	rightHandFrameNo_ =
		MV1SearchFrame(
			trans_.modelId,
			"mixamorig:RightHand"
		);

	leftHandFrameNo_ =
		MV1SearchFrame(
			trans_.modelId,
			"mixamorig:LeftHand"
		);

	Swordtrans_.Update();



	//アニメーションの登録
	std::string path = Application::PATH_MODEL + "CPU/";

	animationController_ = std::make_unique<AnimationController>(trans_.modelId);
	animationController_->Add((int)animType_CPU::Idle_CPU, 20.0f, path + "Great Sword Idle CPU.mv1");
	animationController_->Add((int)animType_CPU::Walk_CPU, 20.0f, path + "Great Sword Walk CPU.mv1");
	animationController_->Add((int)animType_CPU::Attack_CPU, 20.0f, path + "Great Sword SlashCPU.mv1");
	animationController_->Add((int)animType_CPU::Damage_CPU, 20.0f, path + "Standing React Large From Left CPU.mv1");
	animationController_->Add((int)animType_CPU::Lose_CPU, 20.0f, path + "Loss CPU.mv1");
	animationController_->Add((int)animType_CPU::Block_CPU, 20.0f, path + "Block React Large CPU.mv1");
	animationController_->Add((int)animType_CPU::BlockIdle_CPU, 20.0f, path + "Standing Block Idle CPU.mv1");

	CharactorBase::SubInit();
}

void SwordFIghtCPU::SubUpdate(void)
{
	CharactorBase::SubUpdate();

	// 場外
	if (trans_.pos.y < -100)
	{
		ChangeState<SwordFightLoseCPU>();
	}

	if (!KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION).now)isContactTrigger_ = false;

	if (rightHandFrameNo_ != -1 &&
		leftHandFrameNo_ != -1)
	{
		VECTOR rightHandPos =
			MV1GetFramePosition(
				trans_.modelId,
				rightHandFrameNo_
			);

		VECTOR leftHandPos =
			MV1GetFramePosition(
				trans_.modelId,
				leftHandFrameNo_
			);

		// 両手の中心
		VECTOR centerPos = VGet(
			(rightHandPos.x + leftHandPos.x) * 0.5f,
			(rightHandPos.y + leftHandPos.y) * 0.5f - 25.0f,
			(rightHandPos.z + leftHandPos.z) * 0.5f
		);

		centerPos.x += -15.0f;

		Swordtrans_.pos = centerPos;

		Swordtrans_.Update();
	}
}

void SwordFIghtCPU::SubDraw(void)
{
	MV1DrawModel(trans_.modelId);
	MV1DrawModel(Swordtrans_.modelId);
	DrawFormatString(0, 50, 0xffffff, "State:%s", currentState_->GetName());
}

void SwordFIghtCPU::SubRelease(void)
{
}

void SwordFIghtCPU::InitCollider(void)
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

void SwordFIghtCPU::CreateState(void)
{
	AddState(std::make_unique<SwordFightIdleCPU>());
	AddState(std::make_unique<SwordFightBlockCPU>());
	AddState(std::make_unique<SwordFightWalkCPU>());
	AddState(std::make_unique<SwordFightLoseCPU>());
	AddState(std::make_unique<SwordFightDamageCPU>());
	AddState(std::make_unique<SwordFightAttackCPU>());
	AddState(std::make_unique<SwordFightBlockIdleCPU>());
}
float SwordFIghtCPU::GetDistanceToTarget()
{
	return 0.0f;
}
void SwordFIghtCPU::LookTarget()
{
}
void SwordFIghtCPU::InitRigidBody(void)
{
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMoveSpeed(1);
}

void SwordFIghtCPU::ReturnToIdle(void)
{
	ChangeState<SwordFightIdleCPU>();
}
