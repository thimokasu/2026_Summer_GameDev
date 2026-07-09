#include "SwordFightPlayer.h"
#include"../../../../Manager/Generic/KeyManager.h"
#include"../../../../Manager/Game/SceneManager.h"
#include"../../Camera/Camera.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderCapsule.h"
#include"../../../../Manager/Resource/ResourceManager.h"
#include"../../../Common/AnimationController.h"
#include "../../../../Utility/AsoUtility.h"
SwordFightPlayer::SwordFightPlayer(void)
{
	//animationController_ = nullptr;
	//state_ = STATE::NONE;

	//speed_ = 0.0f;
	//moveDir_ = AsoUtility::VECTOR_ZERO;
	//movePow_ = AsoUtility::VECTOR_ZERO;
	//movedPos_ = AsoUtility::VECTOR_ZERO;

	//playerRotY_ = Quaternion();
	//goalQuaRot_ = Quaternion();
	//stepRotTime_ = 0.0f;

	//// 衝突チェック
	//gravHitPosDown_ = AsoUtility::VECTOR_ZERO;
	//gravHitPosUp_ = AsoUtility::VECTOR_ZERO;

	//capsule_ = nullptr;

	//// 状態管理
	//stateChanges_.emplace(STATE::NONE, std::bind(&SwordFightPlayer::ChangeStateNone, this));
	//stateChanges_.emplace(STATE::IDLE, std::bind(&SwordFightPlayer::ChangeStatePlay, this));

}

SwordFightPlayer::~SwordFightPlayer(void)
{
}

void SwordFightPlayer::SubLoad(void)
{
	//trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(SRC::P1));
}

void SwordFightPlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(1000);
	rigidBody_.SetMoveSpeed(1.25f);
	trans_.pos = VGet(0.0f, 40.0f, 0.0f);
	/*trans_.scl = VGet(0.1f, 0.1f, 0.1f);

	InitAnimation();

	ChangeState(STATE::IDLE);*/

}

void SwordFightPlayer::SubUpdate(void)
{

	
	//	stateUpdate_();


	//// モデル制御更新
	//trans_.Update();

	//if (animationController_)
	//{
	//	animationController_->Update();
	//}

	MoveInput();



}

void SwordFightPlayer::SubDraw(void)
{
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
}

void SwordFightPlayer::AddCollider(std::weak_ptr<ColliderBase> collider)
{
	colliders_.push_back(collider);

}

void SwordFightPlayer::ClearCollider(void)
{
	colliders_.clear();
}


void SwordFightPlayer::InitAnimation(void)
{
	/*std::string path = Application::PATH_MODEL + "Player/";
	animationController_ = std::make_unique<AnimationController>(trans_.modelId);
	animationController_->Add((int)ANIM_TYPE::IDLE,  20.0f ,path + "Player Idle.mv1");
	animationController_->Add((int)ANIM_TYPE::WALK,  20.0f ,path + "Walk.mv1");
	animationController_->Add((int)ANIM_TYPE::ATTACK,  20.0f ,path + "Player Attack.mv1");
	animationController_->Add((int)ANIM_TYPE::LOSE,  60.0f ,path + "Lose.mv1");
	animationController_->Add((int)ANIM_TYPE::BLOCK, 60.0f, path + "Block React Large.mv1");
	animationController_->Add((int)ANIM_TYPE::DAMAGE,  60.0f ,path + "DamageReact Large From Left.mv1");

	animationController_->Play((int)ANIM_TYPE::IDLE);*/
}

void SwordFightPlayer::ChangeState(STATE state)
{
	// 状態変更
	state_ = state;

	// 各状態遷移の初期処理
	stateChanges_[state_]();
}

void SwordFightPlayer::ChangeStateNone(void)
{
	stateUpdate_ = std::bind(&SwordFightPlayer::UpdateNone, this);
}

void SwordFightPlayer::ChangeStatePlay(void)
{
	stateUpdate_ = std::bind(&SwordFightPlayer::UpdatePlay, this);
}

void SwordFightPlayer::UpdateNone(void)
{
}

void SwordFightPlayer::UpdatePlay(void)
{
	
	// 移動方向に応じた回転
	Rotate();

	// 重力による移動量
	CalcGravityPow();

	// 衝突判定
	Collision();

	// 回転させる
	trans_.quaRot = playerRotY_;
}


const ColliderCapsule& SwordFightPlayer::GetCapsule(void) const
{
	return *capsule_;
}

void SwordFightPlayer::MoveInput(void)
{
	VECTOR moveVec = { 0.0f, 0.0f, 0.0f };

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now) moveVec.z += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now) moveVec.z -= 1.0f;

	const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera().GetAngles();
	MATRIX camYaw = MGetRotY(cameraAngle.y);
	moveVec = VTransform(moveVec, camYaw);

	if (VSize(moveVec) > 0.0f)
	{
		moveVec = VNorm(moveVec);
	}
	trans_.pos = VAdd(trans_.pos, VScale(moveVec, rigidBody_.GetMoveSpeed()));
}

void SwordFightPlayer::SetGoalRotate(double rotRad)
{
	VECTOR cameraRot = mainCamera.GetAngles();
	Quaternion axis = Quaternion::AngleAxis((double)cameraRot.y + rotRad, AsoUtility::AXIS_Y);

	// 現在設定されている回転との角度差を取る
	double angleDiff = Quaternion::Angle(axis, goalQuaRot_);

	// しきい値
	if (angleDiff > 0.1)
	{
		stepRotTime_ = TIME_ROT;
	}

	goalQuaRot_ = axis;

}

void SwordFightPlayer::Rotate(void)
{
}

void SwordFightPlayer::Collision(void)
{
	//// 現在座標を起点に移動後座標を決める
	//movedPos_ = VAdd(trans_.pos, movePow_);

	//// 衝突(カプセル)
	//CollisionCapsule();

	//// 衝突(重力)
	//CollisionGravity();

	//// 移動
	//trans_.pos = movedPos_;
}

void SwordFightPlayer::CollisionGravity(void)
{
	

	
}

void SwordFightPlayer::CollisionCapsule(void)
{
	
}

void SwordFightPlayer::CalcGravityPow(void)
{
	
}



