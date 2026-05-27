#pragma once
#include<DxLib.h>
#include"ColliderBase.h"
class ActorBase;

class ColliderBox:public ColliderBase
{
public:
	//コンストラクタ
	ColliderBox(ColliderInfo& info, VECTOR& falfSize, ActorBase& actor);
	ColliderBox(ColliderInfo& info, VECTOR& falfSize, ActorBase& actor,int debugColor);
	
	//ボックスの半サイズ取得
	const VECTOR& GetHalfSize(void)const { return halfSize_; }
	//半サイズを設定
	void SetHalfSize(const VECTOR& halfSize) { halfSize_ = halfSize; }

	// 各軸ベクトル取得
	VECTOR GetAxisX(void)const { return GetOwnerTransform().GetRight(); }
	VECTOR GetAxisY(void)const { return GetOwnerTransform().GetUp(); }
	VECTOR GetAxisZ(void)const { return GetOwnerTransform().GetForward(); }

	// ローカル座標⇔ワールド座標変換
	VECTOR Local2World(const VECTOR& localPos) const;
	VECTOR World2Local(const VECTOR& worldPos) const;

	//ボックスの各頂点座標取得
	VECTOR GetVertexPos(int index) const;

private:
	void DrawDebug(int color)override;
	VECTOR halfSize_;
};

