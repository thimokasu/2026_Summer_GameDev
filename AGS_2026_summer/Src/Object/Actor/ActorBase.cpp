#include "ActorBase.h"
#include"../Common/AnimationController.h"
#include"Collider/ColliderBase.h"

ActorBase::ActorBase(void)
{
}

ActorBase::~ActorBase(void)
{
}

void ActorBase::Load(void)
{
	SubLoad();
}

void ActorBase::Init(void)
{
	rigidBody_.SetCentroid(trans_.pos);
	SubInit();
	InitCollider();
}

void ActorBase::Update(void)
{
	SubUpdate();
	rigidBody_.Update();
	Move();
	trans_.Update();
}

void ActorBase::Draw(void)
{
	SubDraw();
	if (isDraw_)MV1DrawModel(trans_.modelId);
}

void ActorBase::Release(void)
{
	SubRelease();
}


void ActorBase::Move(void)
{
	trans_.pos = VAdd(trans_.pos, rigidBody_.GetVelocity());
	
	VECTOR angVel = rigidBody_.GetAngularVelocity();

	float angle = VSize(angVel);

	if (angle > 0.001f)
	{
		VECTOR axis = VScale(angVel, 1.0f / angle);

		Quaternion rot = Quaternion::AngleAxis(angle, axis);

		trans_.quaRot = rot.Mult(trans_.quaRot);

		trans_.quaRot.Normalize();
	}

}
