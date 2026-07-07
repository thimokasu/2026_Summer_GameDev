#include "FindingJRunner.h"
#include <cmath> 
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../../../Scene/GameSelect/GameInfo.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"../../../Manager/ActorManager.h"

FindingJRunner::FindingJRunner(ActorManager& actMana)
	:
	CharactorBase(),
	actorManager_(actMana),
	lastStepTileW_(0),
	lastStepTileD_(0),
	visibleTimer_(0.0f)
{

}

FindingJRunner::~FindingJRunner(void)
{
}

void FindingJRunner::SubLoad(void)
{
}

void FindingJRunner::SubInit(void)
{
	entityKind_ = EntityKind::FINDINGJ_CPU;
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(100);
	rigidBody_.SetMoveSpeed(0.25f);
	trans_.pos = VGet(100.0f, 40.0f, 100.0f);
	isDraw_ = false; 
}
void FindingJRunner::SubUpdate(void)
{
	auto players = actorManager_.FindActorsByKind(EntityKind::PLAYER);
	for (const auto& p : players)
	{
		enemyPositions_.push_back(p->GetTransform().pos);
	}
	timer_ -= SceneManager::GetInstance().GetDeltaTime();
	if (timer_ <= 0.0f)
	{
		Think();
		timer_ = DecisionInterval;
	}
	MoveToTarget();
	enemyPositions_.clear();
	visibleTimer_ -= SceneManager::GetInstance().GetDeltaTime();
	if (visibleTimer_ < 0.0f)
	{
		isDraw_ = false;
	}
	isDraw_ = true;
}

void FindingJRunner::SubDraw(void)
{
	DrawSphere3D(targetPos_, 5.0f, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
}

void FindingJRunner::SubRelease(void)
{
}

void FindingJRunner::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	float radius = 10.0f;
	VECTOR localPosTop = VGet(0.0f, 10.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, -10.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void FindingJRunner::Think(void) // 思考
{
	// 1. 現在のタイルインデックスを『四捨五入』で正確に算出（ズレ防止）
	int curW = static_cast<int>(std::round(trans_.pos.x / TileSize));
	int curD = static_cast<int>(std::round(trans_.pos.z / TileSize));

	// 範囲外を安全にクランプ
	if (curW < 0) curW = 0; if (curW >= W) curW = W - 1;
	if (curD < 0) curD = 0; if (curD >= D) curD = D - 1;

	float bestScore = 1000000.0f;

	// 初期値は現在のマスの中央にしておく
	VECTOR bestTilePos = VGet(curW * TileSize , trans_.pos.y, curD * TileSize );

	// 3. 隣接する9マス（自分を含む）を評価
	for (int dw = -1; dw <= 1; ++dw) {
		for (int dd = -1; dd <= 1; ++dd) {
			int nextW = curW + dw;
			int nextD = curD + dd;

			// 範囲外チェック
			if (nextW < 0 || nextW >= W || nextD < 0 || nextD >= D) continue;

			// ★壁判定を先に行う（壁ならこのマスのスコア計算自体を完全にスキップ！）
			if (Stage3::stage[1][nextD][nextW] != StageLayout::None) continue;

			// ★壁じゃないことを確認してからスコアを0で初期化
			float score = 0.0f;

			// マスの「中央」の座標を計算
			VECTOR tilePos = VGet(nextW * TileSize , trans_.pos.y, nextD * TileSize);

			// 鬼との距離によるペナルティ
			for (const auto& e : enemyPositions_)
			{
				float dist = VSize(VSub(tilePos, e));
				if (dist < 1.0f) dist = 1.0f; // ゼロ割防止
				score += (2000.0f / dist);    // 距離が近いほどペナルティが大きくなる
			}

			// 光る床を通るリスクを考慮
			if (Stage3::stage[0][nextD][nextW] == StageLayout::ReactionBlock)
			{
				score += ReactionBlockPenalty; // 光る床を通るとペナルティ
			}

			// 最もスコアが低い（安全な）マスを更新
			if (score < bestScore) {
				bestScore = score;
				bestTilePos = tilePos;
			}
		}
	}

	targetPos_ = bestTilePos;

	// タイルが切り替わったかチェック
	if (curW != lastStepTileW_ || curD != lastStepTileD_)
	{
		lastStepTileW_ = curW;
		lastStepTileD_ = curD;
	}
}

void FindingJRunner::MoveToTarget(void)
{
	VECTOR moveVec = VSub(targetPos_, trans_.pos);
	if(VSize(moveVec) > 1.0f) // 目的地までの距離がある程度以上なら移動する
	{
		moveVec = VGet(moveVec.x / VSize(moveVec), 0, moveVec.z / VSize(moveVec)); // 正規化
		rigidBody_.AddForce(VGet(moveVec.x * rigidBody_.GetMoveSpeed(), 0, moveVec.z * rigidBody_.GetMoveSpeed()));
	}
}

