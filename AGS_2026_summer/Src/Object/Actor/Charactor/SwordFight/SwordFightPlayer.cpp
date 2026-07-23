#include "SwordFightPlayer.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderCapsule.h"
#include"SwordState/SwordFIghtStateHeaders.h"
#include"../../../../Manager/Generic/KeyManager.h"
#include "../../../Common/AnimationController.h"
#include"../../../../Utility/AsoUtility.h"
#include "../../../../Application.h"
#include"../../../../Manager/Game/SE.h"


SwordFightPlayer::SwordFightPlayer(void)
{
}

SwordFightPlayer::~SwordFightPlayer(void)
{
}

void SwordFightPlayer::SubLoad(void)
{
	CharactorBase::SubLoad();
	//trans_.modelId = MV1LoadModel("Data/Model/Player/Player Idle.mv1");
	//Swordtrans_.modelId = MV1LoadModel("Data/Model/Player/SwordRed.mv1");
	SE::GetInstance().Load(SOUND_TYPE::LOSS, "Data/BGM/SwordFight/Loss.mp3");
	SE::GetInstance().Load(SOUND_TYPE::CUT, "Data/BGM/SwordFight/Cut.mp3");
	SE::GetInstance().Load(SOUND_TYPE::DOME, "Data/BGM/SwordFight/Dome.mp3");
	SE::GetInstance().Load(SOUND_TYPE::DRAW, "Data/BGM/SwordFight/Draw.mp3");
	SE::GetInstance().Load(SOUND_TYPE::HITATTACK, "Data/BGM/SwordFight/HitAttack.mp3");
	SE::GetInstance().Load(SOUND_TYPE::HITSWORD, "Data/BGM/SwordFight/HitSword.mp3");
	SE::GetInstance().Load(SOUND_TYPE::START, "Data/BGM/SwordFight/Start.mp3");
	SE::GetInstance().Load(SOUND_TYPE::START2, "Data/BGM/SwordFight/Start2.mp3");
	SE::GetInstance().Load(SOUND_TYPE::WIN, "Data/BGM/SwordFight/Win.mp3");

}

void SwordFightPlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	trans_.quaRotLocal = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadD(180.0f), 0.0f));


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
	std::string path = Application::PATH_MODEL + "Player/";

	animationController_ = std::make_unique<AnimationController>(trans_.modelId);
	animationController_->Add((int)animType::Idle, 20.0f,path+"Player Idle.mv1");
	animationController_->Add((int)animType::Walk, 20.0f, path + "Great Sword Walk2.mv1");
	animationController_->Add((int)animType::Attack, 20.0f, path + "Player Attack.mv1");
	animationController_->Add((int)animType::Damage, 20.0f, path + "DamageReact Large From Left.mv1");
	animationController_->Add((int)animType::Lose, 20.0f, path + "Lose.mv1");
	animationController_->Add((int)animType::Block, 20.0f, path + "Block React Large.mv1");
	animationController_->Add((int)animType::BlockIdle, 20.0f, path + "Standing Block Idle.mv1");

	CharactorBase::SubInit();
}

void SwordFightPlayer::SubUpdate(void)
{
	CharactorBase::SubUpdate();
	if (!KEY::GetIns().GetInfo(KEY::KEY_TYPE::J_KEY_ACTION).now)isContactTrigger_ = false;
	UpdateSword();
}

void SwordFightPlayer::SubDraw(void)
{
	MV1DrawModel(trans_.modelId);
	MV1DrawModel(Swordtrans_.modelId);
	DrawFormatString(0, 10, 0xffffff, "State:%s", currentState_->GetName());
	SE::GetInstance().Play(SOUND_TYPE::START, false);

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
	ownColliders_.emplace(static_cast<int>(100), std::move(collider));
}

void SwordFightPlayer::CreateState(void)
{
	AddState(std::make_unique<SwordFight_Idle>());
	AddState(std::make_unique<SwordFight_Block>());
	AddState(std::make_unique<SwordFIght_Walk>());
	AddState(std::make_unique<SwordFight_Lose>());
	AddState(std::make_unique<SwordFight_Damage>());
	AddState(std::make_unique<SwordFight_Attack>());
	AddState(std::make_unique<SwordFight_BlockIdle>());
}

bool SwordFightPlayer::IsAttacking() const
{
	return dynamic_cast<SwordFight_Attack*>(currentState_) != nullptr;
}

void SwordFightPlayer::UpdateSword()
{
	if (rightHandFrameNo_ != -1)
	{
		// 右手ボーンのワールド行列
		MATRIX handMat =
			MV1GetFrameLocalWorldMatrix(
				trans_.modelId,
				rightHandFrameNo_);

		// 剣を握る位置の微調整
		MATRIX offsetMat = MGetIdent();

		// 位置調整（手から見た位置）
		offsetMat = MMult(
			offsetMat,
			MGetTranslate(
				VGet(-4.5f, -17.0f, 0.0f)));

		// 角度調整
		offsetMat = MMult(
			offsetMat,
			MGetRotZ(AsoUtility::Deg2RadD(-45.0f)));

		// 必要ならX,Yも調整
		// offsetMat = MMult(offsetMat, MGetRotX(...));
		// offsetMat = MMult(offsetMat, MGetRotY(...));

		// スケール
		MATRIX scaleMat = MGetScale(VGet(2.5f, 3.0f, 2.8f));

		// ボーン行列 × オフセット
		MATRIX swordMat = MMult(offsetMat, handMat);

		// スケールを適用
		swordMat = MMult(scaleMat, swordMat);

		MV1SetMatrix(
			Swordtrans_.modelId,
			swordMat);
	}
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



