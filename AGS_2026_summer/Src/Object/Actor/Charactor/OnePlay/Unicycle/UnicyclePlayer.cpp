#include "UnicyclePlayer.h"
#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"

UnicyclePlayer::UnicyclePlayer(void)
{
}

UnicyclePlayer::~UnicyclePlayer(void)
{
}

void UnicyclePlayer::SubLoad(void)
{
	trans_.modelId = MV1LoadModel("Data/Unicycle/Player/Redcycle.mv1");
}

void UnicyclePlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(1000);
	rigidBody_.SetMoveSpeed(1.0f);
	trans_.pos = VGet(0.0f, 40.0f, 0.0f);
}

void UnicyclePlayer::SubUpdate(void)
{
	MoveInput();
}

void UnicyclePlayer::SubDraw(void)
{
	MV1DrawModel(trans_.modelId);
}

void UnicyclePlayer::SubRelease(void)
{
}

void UnicyclePlayer::InitCollider(void)
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

void UnicyclePlayer::MoveInput(void)
{
	VECTOR moveVec = { 0.0f, 0.0f, 0.0f };

	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_FRONT).now) moveVec.z += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_BACK).now) moveVec.z -= 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now) moveVec.x += 1.0f;
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now) moveVec.x -= 1.0f;

	const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera().GetAngles();
	MATRIX camYaw = MGetRotY(cameraAngle.y);
	moveVec = VTransform(moveVec, camYaw);

	if (VSize(moveVec) > 0.0f)
	{
		moveVec = VNorm(moveVec);
	}
	trans_.pos = VAdd(trans_.pos, VScale(moveVec, rigidBody_.GetMoveSpeed()));
}
