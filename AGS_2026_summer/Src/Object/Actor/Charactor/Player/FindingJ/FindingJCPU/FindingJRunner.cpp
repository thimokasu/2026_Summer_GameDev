#include "FindingJRunner.h"
#include <cmath> 
#include"../../../../../../Manager/Game/SceneManager.h"
#include"../../../../../../Scene/GameSelect/GameKind.h"
#include"../../../../Collider/ColliderBase.h"
#include"../../../../Collider/ColliderCapsule.h"
#include"../../../../Manager/ActorManager.h"

FindingJRunner::FindingJRunner(ActorManager& actMana)
	:
	CharactorBase(),
	actorManager_(actMana),
	lastStepTileW_(0),
	lastStepTileD_(0),
	visibleTimer_(0.0f),
	stageNum_(static_cast<int>(FourPlayer::FindingJ::Stage::Stage3))
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
	rigidBody_.SetMoveSpeed(0.5f);
	trans_.pos = VGet(100.0f, 40.0f, 100.0f);

}
void FindingJRunner::SubUpdate(void)
{
	auto players = actorManager_.FindActorsByKind(EntityKind::PLAYER);
	for (const auto& p : players)
	{
		enemyPositions_.push_back(p->GetTransform().pos);
	}
	Think();
	MoveToTarget();
	enemyPositions_.clear();
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
	//現在のタイルインデックスを取得
	int curW = static_cast<int>(trans_.pos.x / TileSize);
	int curD = static_cast<int>(trans_.pos.z / TileSize);
	float bestScore = 10000.0f;
	VECTOR bestTilePos = targetPos_;


	//隣接する9マスを評価
	for (int dw = -1; dw <= 1; ++dw) {
		for (int dd = -1; dd <= 1; ++dd) {
			int nextW = curW + dw;
			int nextD = curD + dd;

			// 範囲外チェック
			if (nextW < 0 || nextW >= W || nextD < 0 || nextD >= D) continue;
			if (dw == 0 && dd == 0) continue; // 現在のタイルはスキップ
			switch (stageNum_)
			{
			case static_cast<int>(FourPlayer::FindingJ::Stage::Stage1):
				if (Stage1::stage[0][nextW][nextD] == StageLayout::Block) continue;
				break;
			case static_cast<int>(FourPlayer::FindingJ::Stage::Stage2):
				if (Stage2::stage[0][nextW][nextD] == StageLayout::Block) continue;
				break;
			case static_cast<int>(FourPlayer::FindingJ::Stage::Stage3):
				if (Stage3::stage[0][nextW][nextD] == StageLayout::Block) continue;
				break;
			}

			// スコア計算
			float score = 0;
			VECTOR tilePos = VGet(nextW * TileSize, 0, nextD * TileSize);
			//鬼との距離によるペナルティー
			for (const auto& e : enemyPositions_)
			{
				float dist = VSize(VSub(tilePos, e));
				if (dist < 1.0f)dist = 1.0f; // ゼロ割防止
				score += (2000.0f / dist); // 距離が近いほどスコアが高くなる
			}
			//光る床を通るリスクを考慮
			switch (stageNum_)
			{
			case static_cast<int>(FourPlayer::FindingJ::Stage::Stage1):
				if (Stage1::stage[0][nextW][nextD] == StageLayout::ReactionBlock)
					score += ReactionBlockPenalty;
				break;
			case static_cast<int>(FourPlayer::FindingJ::Stage::Stage2):
				if (Stage2::stage[0][nextW][nextD] == StageLayout::ReactionBlock)
					score += ReactionBlockPenalty;
				break;
			case static_cast<int>(FourPlayer::FindingJ::Stage::Stage3):
				if (Stage3::stage[0][nextW][nextD] == StageLayout::ReactionBlock)
					score += ReactionBlockPenalty;
				break;
			}
			if (score < bestScore) {
				bestScore = score;
				bestTilePos = VGet(nextW * TileSize + (TileSize / 2.0f), 0, nextD * TileSize + (TileSize / 2.0f));
			}
		}
	}
	targetPos_ = bestTilePos;

	// CPUの更新処理内
	int W = static_cast<int>(trans_.pos.x / TileSize);
	int D = static_cast<int>(trans_.pos.z / TileSize);

	// タイルが切り替わったかチェック
	if (curW != lastStepTileW_ || curD != lastStepTileD_)
	{
		// 現在のタイルを「前回のタイル」として保存
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

