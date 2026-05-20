#pragma once
#include<DxLib.h>


class RigidBody
{
public:

	enum class BodyType
	{
		STATIC,		//静的
		DYNAMIC,	//動的
		KINEMATIC,	//キネマティック
	};

	static constexpr float GRAVITY = 0.981f;	//重力加速度
	RigidBody(void);
	~RigidBody(void);

	void Update(void);

	void SetBodyType(BodyType type);
	void SetMass(float mass);
	void SetUseGravity(bool useGravity);
	void SetGrounded(bool isGrounded);
	void SetVelocity(VECTOR velocity);
	void AddForce(VECTOR force);
	void SetMoveSpeed(float speed);
	void SetJumpForce(float force);
	void SetMaxMoveSpeed(float maxSpeed);

	BodyType GetBodyType(void) const { return bodyType_; }
	float GetMass(void) const { return mass_; }
	float GetInverseMass(void) const { return inverseMass_; }
	VECTOR GetVelocity(void) const { return velocity_; }
	bool IsUsingGravity(void) const { return useGravity_; }
	bool IsGrounded(void) const { return isGrounded_; }
	float GetRestitution(void) const { return restitution_; }
	float GetFriction(void) const { return friction_; }
	float GetMoveSpeed(void) const { return moveSpeed_; }
	float GetJumpForce(void) const { return jumpForce_; }
	float GetMaxMoveSpeed(void) const { return maxMoveSpeed_; }

	void ClearForces(void) { force_ = { 0.0f, 0.0f, 0.0f }; }
	void ClearGravity(void) { force_.y = 0.0f; }

private:
	BodyType bodyType_;	//剛体の種類
	float mass_;		//質量
	float inverseMass_;	//逆質量
	VECTOR velocity_;	//速度
	VECTOR force_;		//加わっている力
	bool useGravity_;	//重力を使用するか
	bool isGrounded_;	//地面に接しているか

	float restitution_ = -1;	//反発係数
	float friction_ = -1;		//摩擦係数

	float moveSpeed_;		//移動速度
	float jumpForce_;		//ジャンプ力

	float maxMoveSpeed_ = -1;	//最大移動速度

};

using Body = RigidBody::BodyType;