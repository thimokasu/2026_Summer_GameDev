#include "Player.h"
#include<memory>
#include"../../Collider/ColliderInfo.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderCapsule.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

Player::Player(VECTOR pos)
{
}

void Player::SubLoad(void)
{
}

void Player::SubInit(void)
{
}

void Player::SubUpdate(void)
{
}

void Player::SubDraw(void)
{
}

void Player::SubRelease(void)
{
}

void Player::InitCollider(void)
{
	ColliderInfo info = {
	SHAPE::CAPSULE,
	&trans_,
	TAG::PLAYER,
	Layer::ACTOR,
	ColliderBase::SetMask({Layer::ACTOR}),
	VGet(0.0f, 0.0f, 0.0f),
	VGet(0.0f, 0.0f, 0.0f),
	false,
	true,
	};

	std::shared_ptr<ColliderCapsule> collider =
		std::make_shared<ColliderCapsule>(info,radius_,topPos,downPos,this);
	ownColliders_.emplace(static_cast<int>(SHAPE::CAPSULE), collider);
}
