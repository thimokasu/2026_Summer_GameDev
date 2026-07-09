#pragma once
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <DxLib.h>

#include "../CharactorBase.h"
class ColliderBase;
class ColliderCapsule;
class AnimationController;

class SwordFightPlayer :
	public CharactorBase
{
public:

	// スピード
	static constexpr float SPEED_MOVE = 5.0f;
	static constexpr float SPEED_RUN = 10.0f;

	// 回転完了までの時間
	static constexpr float TIME_ROT = 1.0f;

	// 状態
	enum class STATE
	{
		NONE,
		IDLE,
		WALK,
		ATTACK,
		LOSE,
		BLOCK,
		DAMAGE,
	};

	// アニメーション種別
	enum class ANIM_TYPE
	{
		IDLE,
		WALK,
		ATTACK,
		LOSE,
		BLOCK,
		DAMAGE,
	};


	SwordFightPlayer(void);
	virtual ~SwordFightPlayer(void);
	void SubLoad(void) override;
	void SubInit(void) override;
	void SubUpdate(void) override;
	void SubDraw(void) override;
	void SubRelease(void) override;
	void InitCollider(void) override;

	// 衝突判定に用いられるコライダ制御
	void AddCollider(std::weak_ptr<ColliderBase> collider);
	void ClearCollider(void);

	// 衝突用カプセルの取得
	const ColliderCapsule& GetCapsule(void) const;

private:

	// アニメーション
	std::unique_ptr<AnimationController> animationController_;

	// 状態管理
	STATE state_;
	// 状態管理(状態遷移時初期処理)
	std::map<STATE, std::function<void(void)>> stateChanges_;
	// 状態管理(更新ステップ)
	std::function<void(void)> stateUpdate_;

	// 移動スピード
	float speed_;

	// 移動方向
	VECTOR moveDir_;

	// 移動量
	VECTOR movePow_;

	// 移動後の座標
	VECTOR movedPos_;

	// 回転
	Quaternion playerRotY_;
	Quaternion goalQuaRot_;
	float stepRotTime_;

	// 衝突判定に用いられるコライダ
	std::vector<std::weak_ptr<ColliderBase>> colliders_;
	std::unique_ptr<ColliderCapsule> capsule_;

	// 衝突チェック
	VECTOR gravHitPosDown_;
	VECTOR gravHitPosUp_;

	// 重力による移動量
	virtual void MoveInput(void) override;

	void InitAnimation(void);

	// 状態遷移
	void ChangeState(STATE state);
	void ChangeStateNone(void);
	void ChangeStatePlay(void);

	// 更新ステップ
	void UpdateNone(void);
	void UpdatePlay(void);



	// 回転
	void SetGoalRotate(double rotRad);
	void Rotate(void);

	// 衝突判定
	void Collision(void);
	void CollisionGravity(void);
	void CollisionCapsule(void);

	// 移動量の計算
	void CalcGravityPow(void);

};

