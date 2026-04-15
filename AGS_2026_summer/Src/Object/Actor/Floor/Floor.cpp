#include "Floor.h"
#include<memory>
#include"../Collider/ColliderBox.h"
Floor::Floor(void)
{
}

Floor::Floor(VECTOR size)
    :
    ActorBase(),
    size_(size)
{
}

Floor::~Floor(void)
{
}

void Floor::SubInit(void)
{
    trans_.pos = VGet(0.0f, size_.y * -1, 0.0f);

}

void Floor::SubUpdate(void)
{
    int a = 1;
}

void Floor::SubDraw(void)
{
}

void Floor::SubRelease(void)
{
}

void Floor::InitCollider(void)
{
    ColliderInfo info = {
SHAPE::BOX,
&trans_,
TAG::STAGE,
Layer::STAGE,
ColliderBase::SetMask({ Layer::ACTOR }),
VGet(0.0f, 0.0f, 0.0f),
VGet(0.0f, 0.0f, 0.0f),
false,
true,
GetColor(255,0,0)
    };
    std::shared_ptr<ColliderBox> collider =
        std::make_shared<ColliderBox>(info, size_,this);
    ownColliders_.emplace(static_cast<int>(SHAPE::BOX), collider);
}
