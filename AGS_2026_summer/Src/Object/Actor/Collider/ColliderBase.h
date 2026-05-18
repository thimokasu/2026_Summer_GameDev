#pragma once
#include<DxLib.h>
#include"ColliderInfo.h"
#include"../../Actor/ActorBase.h"
#include"../../Common/Transform.h"



class ColliderBase
{
public:
	ColliderBase(void) = delete;

	ColliderBase(ColliderInfo& info, ActorBase& owner)
		: colliderInfo_(info)
		, ownerActor_(owner)
		, ownerTransform_(owner.GetTransform())
	{
	}

	ColliderBase(ColliderInfo& info, ActorBase& owner, Transform& ownerTrans)
		: colliderInfo_(info)
		, ownerActor_(owner)
		, ownerTransform_(ownerTrans)
	{
	}
	virtual ~ColliderBase(void);

	virtual void Update(void);//更新
	virtual void Draw(void);//描画

	//コライダー情報取得
	const ColliderInfo& GetColliderInfo(void)const { return colliderInfo_; }
	//親取得
	ActorBase& GetOwnerActor(void)const { return ownerActor_; }
	Transform& GetOwnerTransform(void)const { return ownerTransform_; }

	//レイヤーマッチ判定
	static bool IsLayerMatch(const Layer& layerA, const uint32_t& maskA)
	{
		return(maskA & LAYER_BIT(layerA)) != 0;
	}
	//レイヤーマスク生成
	static uint32_t SetMask(std::initializer_list<Layer> layers)
	{
		uint32_t mask = 0;
		for (Layer layer : layers)
			mask |= LAYER_BIT(layer);
		return mask;
	}
	//ローカル座標から開店後のワールド座標を取得
	VECTOR GetRotPos(const VECTOR& localPos)const;
	//デバッグ描画するかどうか
	void SetIsDebug(bool isDebug) { isDebug_ = isDebug;}
protected:
#pragma region 関数
	virtual void DrawDebug(int color) {};//デバッグ描画
	//レイヤービット取得
	static constexpr uint32_t LAYER_BIT(const Layer& layer)
	{
		return 1 << static_cast<uint32_t>(layer);
	}
#pragma endregion

#pragma region 変数
	ColliderInfo colliderInfo_;
	ActorBase& ownerActor_;
	Transform& ownerTransform_;
	bool isDebug_ = true;//デバッグ描画するかどうか
#pragma endregion
};