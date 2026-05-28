#include "RunnerAIComponent.h"
#include "../../../ActorBase.h"
#include "../../../../../Manager/Game/SceneManager.h"

RunnerAIComponent::RunnerAIComponent()
{
    timer_ = DecisionInterval;
    lastStepTileW_ = -1; 
    lastStepTileD_ = -1; 
    visibleTimer_ = 0.0f; 

}

void RunnerAIComponent::Update() {

    timer_ -= SceneManager::GetInstance().GetDeltaTime();
    if (timer_ <= 0.0f) {
        Think();
        timer_ = DecisionInterval;
    }
    Visible();
    if (visibleTimer_ > 0.0f)
    {
        visibleTimer_ -= SceneManager::GetInstance().GetDeltaTime();
    }
    
}

void RunnerAIComponent::Think() {
    // 1. 現在のタイルインデックスを算出
    int curW = static_cast<int>(x_ / TileSize);
    int curD = static_cast<int>(z_ / TileSize);

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
            if (Stage3::stage[1][nextD][nextW] != StageLayout::None) continue;

            // スコア計算
            float score = CalculateTileScore(nextW, nextD, enemyPositions_);

            if (score < bestScore) {
                bestScore = score;
                bestTilePos = VGet(nextW * TileSize + (TileSize / 2.0f), 0, nextD * TileSize + (TileSize / 2.0f));
            }
        }
    }
    targetPos_ = bestTilePos;
}

void RunnerAIComponent::Visible()
{
    // CPUの更新処理内
    int curW = static_cast<int>(x_ / TileSize);
    int curD = static_cast<int>(z_ / TileSize);

    // タイルが切り替わったかチェック
    if (curW != lastStepTileW_ || curD != lastStepTileD_)
    {
        // 現在のタイルを「前回のタイル」として保存
        lastStepTileW_ = curW;
        lastStepTileD_ = curD;
    }
}

float RunnerAIComponent::CalculateTileScore(int tw, int td, const std::vector<VECTOR>& enemyPos) {
    float score = 0.0f;
    VECTOR tilePos = VGet(tw * TileSize, 0, td * TileSize);

    // 鬼との距離によるペナルティ（近いほど高スコア＝危険）
    for (const auto& e : enemyPos) {
        float dist = VSize(VSub(tilePos, e));
        if (dist < 1.0f) dist = 1.0f; // ゼロ除算防止
        score += (2000.0f / dist);
    }

    // 光る床を通るリスクを考慮
    if (Stage3::stage[0][td][tw] == StageLayout::ReactionBlock) {
        score += ReactionBlockPenalty;
    }

    return score;
}