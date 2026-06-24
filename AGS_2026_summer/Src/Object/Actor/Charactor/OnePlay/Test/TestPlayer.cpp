#include "TestPlayer.h"

#include"../../../../../Manager/Generic/KeyManager.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../Camera/Camera.h"

#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"../../../Collider/ColliderBox.h"

TestPlayer::TestPlayer(void)
{
}

TestPlayer::~TestPlayer(void)
{
}

void TestPlayer::SubLoad(void)
{
}

void TestPlayer::SubInit(void)
{
	entityKind_ = EntityKind::PLAYER;
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(1000);
	rigidBody_.SetMoveSpeed(1.0f);
	rigidBody_.SetUseRotation(true);
	trans_.pos = VGet(0.0f, 40.0f, 0.0f);
}

void TestPlayer::SubUpdate(void)
{
	MoveInput();
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).now)
	{
		rigidBody_.AddForce({ 0.0f,3.0f,0.0f });
	}
}

void TestPlayer::SubDraw(void)
{
}

void TestPlayer::SubRelease(void)
{
}

void TestPlayer::InitCollider(void)
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
	

	//	ColliderInfo info;
	//info.shape_ = ColliderShape::BOX;
	//info.layer_ = ColliderLayer::ACTOR;
	//info.mask_ = ColliderBase::SetMask({  Layer::ACTOR,Layer::STAGE });
	//info.localPos_ = { 0.0f,0.0f,0.0f };
	//info.localRot_ = { 0.0f,0.0f,0.0f };
	//info.isTrigger_ = false;
	//info.isActive_ = true;
	//info.debugColor_ = GetColor(0, 255, 0);
	//VECTOR halfSize_ = { 20.0f,20.0f,20.0f };
	//std::unique_ptr<ColliderBase> collider =
	//	std::make_unique<ColliderBox>(info, halfSize_, *this);
	//ownColliders_.emplace(static_cast<int>(ColliderShape::BOX), std::move(collider));

}
void TestPlayer::MoveInput(void)
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
