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
	
}

SwordFightPlayer::~SwordFightPlayer(void)
{
}

void SwordFightPlayer::SubLoad(void)
{
	trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(SRC::P1));
}

void SwordFightPlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(1000);
	rigidBody_.SetMoveSpeed(1.25f);
	trans_.pos = VGet(0.0f, 40.0f, 0.0f);
}

void SwordFightPlayer::SubUpdate(void)
{
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


void SwordFightPlayer::InitAnimation(void)
{
	std::string path = Application::PATH_MODEL + "Player/";
	animationController_ = std::make_unique<AnimationController>(trans_.modelId);
	animationController_->Add((int)ANIM_TYPE::IDLE,  20.0f ,path + "Idle.mv1");
	animationController_->Add((int)ANIM_TYPE::WALK,  20.0f ,path + "Walk.mv1");
	animationController_->Add((int)ANIM_TYPE::ATTACK,  20.0f ,path + "Player Attack.mv1");
	animationController_->Add((int)ANIM_TYPE::LOSE,  60.0f ,path + "Lose.mv1");
	animationController_->Add((int)ANIM_TYPE::BLOCK, 60.0f, path + ".Block React Largemv1");
	animationController_->Add((int)ANIM_TYPE::DAMAGE,  60.0f ,path + "DamageReact Large From Left.mv1");

	animationController_->Play((int)ANIM_TYPE::IDLE);
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


