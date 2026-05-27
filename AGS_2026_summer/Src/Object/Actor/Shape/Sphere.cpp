#include "Sphere.h"
#include<memory>
#include"../Collider/ColliderInfo.h"
#include"../Collider/ColliderBase.h"
#include"../Collider/ColliderSphere.h"

Sphere::Sphere(void)
	: ShapeBase(), radius_(50.0f)
{
}

Sphere::Sphere(float radius)
	: ShapeBase(), radius_(radius)
{
}

Sphere::~Sphere(void)
{
}

void Sphere::SubLoad(void)
{

}

void Sphere::SubInit(void)
{

}	

void Sphere::SubUpdate(void)
{
}

void Sphere::SubDraw(void)
{
}

void Sphere::SubRelease(void)
{
}

void Sphere::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::SPHERE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ ColliderLayer::ACTOR,ColliderLayer::STAGE });
	info.localPos_ = VECTOR{ 0,0,0 };
	info.localRot_ = VECTOR{ 0,0,0 };
	info.isTrigger_ = false;
	info.isActive_ = true;
	std::unique_ptr<ColliderSphere> collider =
		std::make_unique<ColliderSphere>(info, radius_, *this);
	ownColliders_.emplace(static_cast<int>(ColliderShape::SPHERE), std::move(collider));
}