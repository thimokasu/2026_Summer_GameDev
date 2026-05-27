#include "ColliderBase.h"


ColliderBase::~ColliderBase(void)
{
}

void ColliderBase:: Update(void)
{

}

void ColliderBase::Draw(void)
{
	 DrawDebug(colliderInfo_.debugColor_);
}


VECTOR ColliderBase::GetRotPos(const VECTOR& localPos) const
{
	// 追従相手の回転に合わせて指定ローカル座標を回転し、
	// 基準座標に加えることでワールド座標へ変換
	VECTOR localRotPos = ownerTransform_.quaRot.PosAxis(localPos);
	return VAdd(ownerTransform_.pos, localRotPos);
}
