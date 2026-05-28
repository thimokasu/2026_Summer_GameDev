#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include<map>
#include"../Common/Transform.h"
#include"../Common/RigidBody.h"
#include"EntityKind.h"
#include"Collider/ColliderInfo.h"

class AnimationController;
class ColliderBase;

class ActorBase
{
public:
	ActorBase(void);
	virtual ~ActorBase(void);

	//読み込み
	void Load(void);
	//初期化
	void Init(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Release(void);

	//トランスフォーム取得
	Transform& GetTransform(void) { return trans_; }
	//リジッドボディ取得
	RigidBody& GetRigidBody(void) { return rigidBody_; }
	//エンティティID設定
	void SetEntityID(int id) { entityID_ = id; }
	//エンティティID取得
	int GetEntityID(void) const { return entityID_; }
	//エンティティ種別設定
	void SetEntityKind(EntityKind kind) { entityKind_ = kind; }
	//エンティティ種別取得
	EntityKind GetEntityKind(void) const { return entityKind_; }
	//アクティブ状態取得
	bool GetIsActive(void) const { return isActive_; }
	//アクティブ状態設定
	void SetIsActive(bool isActive) { isActive_ = isActive; }
	//自身のコライダーリスト取得
	const std::map<int, std::unique_ptr<ColliderBase>>& GetOwnColliders(void) const { return ownColliders_; }
	//描画状態取得
	bool IsDraw(void) const { return isDraw_; }
	//描画状態設定
	void SetIsDraw(bool isDraw) { isDraw_ = isDraw; }
protected:
#pragma region 関数
	virtual void SubLoad(void) {};
	virtual void SubInit(void) {};
	virtual void SubUpdate(void) {};
	virtual void SubDraw(void) {};
	virtual void SubRelease(void) {};

	virtual void InitCollider(void) {};

	void Move(void);
#pragma endregion

#pragma region 変数
	//アニメーションコントローラー
	std::unique_ptr<AnimationController> animationController_;
	//トランスフォーム
	Transform trans_;
	//リジッドボディ
	RigidBody rigidBody_;
	//エンティティID
	int entityID_;
	//エンティティ種別
	EntityKind entityKind_;
	//描画状態
	bool isDraw_ = true;
	//アクティブ状態
	bool isActive_;
	//自身のコライダーリスト
	std::map<int, std::unique_ptr<ColliderBase>> ownColliders_;
#pragma endregion
};