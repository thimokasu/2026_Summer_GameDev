#include "RunnerAIComponent.h"
#include "../../../ActorBase.h"

RunnerAIComponent::RunnerAIComponent()
{
}

void RunnerAIComponent::Update(float deltaTime) {
    
    auto owner = OnAttach()
    auto pos = owner->GetPosition();
    x_ = pos.x;
    z_ = pos.z;

    timer_ -= deltaTime;
    if (timer_ <= 0.0f) {
        Think();
        timer_ = DecisionInterval;
    }
}

void RunnerAIComponent::Think() {
    // 1. 現在のタイルインデックスを算出
    int curW = static_cast<int>(x_ / TileSize);
    int curD = static_cast<int>(z_ / TileSize);

    // 2. 鬼の位置を取得（GameManager経由などを想定）
    // std::vector<VECTOR> enemyPos = GameManager::GetInstance().GetEnemyPositions();
    std::vector<VECTOR> enemyPos; // 一旦空とする

    float bestScore = 1000000.0f;
    VECTOR bestTilePos = targetPos_;

    // 3. 隣接する9マス（自分を含む）を評価
    for (int dw = -1; dw <= 1; ++dw) {
        for (int dd = -1; dd <= 1; ++dd) {
            int nextW = curW + dw;
            int nextD = curD + dd;

            // 範囲外チェック
            if (nextW < 0 || nextW >= W || nextD < 0 || nextD >= D) continue;

            // 高さ1が壁（None以外）なら通れない
            if (Stage1::stage[1][nextD][nextW] != StageLayout::None) continue;

            // スコア計算
            float score = CalculateTileScore(nextW, nextD, enemyPos);

            if (score < bestScore) {
                bestScore = score;
                bestTilePos = VGet(nextW * TileSize + (TileSize / 2.0f), 0, nextD * TileSize + (TileSize / 2.0f));
            }
        }
    }
    targetPos_ = bestTilePos;
}

float RunnerAIComponent::CalculateTileScore(int tw, int td, const std::vector<VECTOR>& enemyPos) {
    float score = 0.0f;
    VECTOR tilePos = VGet(tw * TileSize, 0, td * TileSize);

    // 鬼との距離によるペナルティ（近いほど高スコア＝危険）
    for (const auto& e : enemyPos) {
        float dist = VSize(VSub(tilePos, e));
        if (dist < 1.0f) dist = 1.0f; // ゼロ除算防止
        score += (1000.0f / dist);
    }

    // 光る床を通るリスクを考慮
    if (Stage1::stage[0][td][tw] == StageLayout::ReactionBlock) {
        score += ReactionBlockPenalty;
    }

    return score;
}