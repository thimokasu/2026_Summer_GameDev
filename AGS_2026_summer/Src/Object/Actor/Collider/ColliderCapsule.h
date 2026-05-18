#pragma once
#include "ColliderBase.h"

class ColliderCapsule :
    public ColliderBase
{
public:
	//コンストラクタ
	ColliderCapsule(ColliderInfo&info,float radius,
		VECTOR& localPosTop, VECTOR& localPosDown, ActorBase& actor);

	//親Transformからの相対位置を取得
	const VECTOR& GetLocalPosTop(void)const { return localPosTop_; }
	const VECTOR& GetLocalPosDown(void)const { return localPosDown_; }
	//半径取得
	float GetRadius(void)const { return radius_; }
	//半径設定
	void SetRadius(float radius) { radius_ = radius; }
	//高さ
	float GetHeight(void)const;
	// ワールド座標を取得
	VECTOR GetPosTop(void) const;
	VECTOR GetPosDown(void) const;
	// カプセルの中心座標
	VECTOR GetCenter(void) const;
private:
	//カプセルの上端のローカル位置
	VECTOR localPosTop_;
	//カプセルの下端のローカル位置
	VECTOR localPosDown_;
	//半径
	float radius_;
	// デバッグ描画
	void DrawDebug(int color) override;
};

