#include "Player.h"
#include<DxLib.h>
#include"../../Camera/Camera.h"
#include"../../../../Manager/Game/SceneManager.h"
#include"../../../../Manager/Generic/KeyManager.h"
#include"../../../../Net/NetManager.h"
Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::SubLoad(void)
{
	InitCollider();
}

void Player::SubInit(void)
{
}

void Player::SubUpdate(void)
{
	MoveInput();
}

void Player::SubDraw(void)
{
}

void Player::SubRelease(void)
{
}

void Player::MoveInput(void)
{
	VECTOR moveDir = VGet(0.0f, 0.0f, 0.0f);
	bool isAction = false;
	auto& nIns = NetManager::GetInstance();	
	using PAction = PLAYER_ACTION;
	isAction = KeyManager::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_UP).now;
	if (nIns.IsAction(
		netPlayerID_.userID,
		PAction::MOVE_FORWARD, isAction))
	{
		moveDir.z += 1.0f;
		if (netPlayerID_.userID == nIns.GetSelf().key)
		{
			nIns.SetAction(PAction::MOVE_FORWARD);
		}
	}

	isAction = KeyManager::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_DOWN).now;

	if (nIns.IsAction(
		netPlayerID_.userID,
		PAction::MOVE_BACK, isAction))
	{
		moveDir.z -= 1.0f;
		if (netPlayerID_.userID == nIns.GetSelf().key)
		{
			nIns.SetAction(PAction::MOVE_BACK);
		}
	}

	isAction = KeyManager::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_RIGHT).now;

	if (nIns.IsAction(
		netPlayerID_.userID,
		PAction::MOVE_RIGHT, isAction))
	{
		moveDir.x += 1.0f;
		if (netPlayerID_.userID == nIns.GetSelf().key)
		{
			nIns.SetAction(PAction::MOVE_RIGHT);
		}
	}

	isAction = KeyManager::GetIns().GetInfo(KEY::KEY_TYPE::MOVE_LEFT).now;

	if (nIns.IsAction(
		netPlayerID_.userID,
		PAction::MOVE_LEFT, isAction))
	{
		moveDir.x -= 1.0f;
		if (netPlayerID_.userID == nIns.GetSelf().key)
		{
			nIns.SetAction(PAction::MOVE_LEFT);
		}
	}

	const VECTOR cameraAngle = SceneManager::GetInstance().GetCamera()->GetAngles();
	MATRIX camYaw = MGetRotY(cameraAngle.y);
	moveDir = VTransform(moveDir, camYaw);
	if(VSize(moveDir) > 0.0f)
	{
		moveDir = VNorm(moveDir);
	}
	if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::SPACE).down)
	{
		rigidBody_.SetVelocity(
			VAdd(
				rigidBody_.GetVelocity(), 
				VGet(0, rigidBody_.GetJumpForce(),
					0)
			)
		);
	}

	rigidBody_.AddForce(VScale(moveDir, rigidBody_.GetMoveSpeed()));	
}
