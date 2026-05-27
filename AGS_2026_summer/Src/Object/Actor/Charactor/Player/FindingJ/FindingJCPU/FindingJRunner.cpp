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
	stageNum_(0)
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
	Think();
}


void FindingJRunner::SubUpdate(void)
{
}

void FindingJRunner::SubDraw(void)
{
}

void FindingJRunner::SubRelease(void)
{
}

void FindingJRunner::InitCollider(void)
{
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

			// 高さ1が壁（None以外）なら通れない
			if (Stage1::stage[1][nextD][nextW] != StageLayout::None) continue;

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

