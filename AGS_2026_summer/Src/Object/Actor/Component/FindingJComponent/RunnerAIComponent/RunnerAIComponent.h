#pragma once
#include "../../ComponentBase.h"
#include "../../../Stage/FindingJ/StageLayout.h"
#include <vector>


class RunnerAIComponent :
    public ComponentBase
{
public:
    static constexpr float DecisionInterval = 0.01f; // 思考間隔（秒）
    static constexpr float ReactionBlockPenalty = 30.0f; // 光る床を通る際のリスク加算

private:
    float x_ = 0.0f;
    float z_ = 0.0f;
    float timer_ = 0.0f;

    VECTOR targetPos_ = VGet(0, 0, 0); 

    std::vector<VECTOR> enemyPositions_; // 鬼の位置リスト

public:
    RunnerAIComponent();
    virtual ~RunnerAIComponent() = default;

    void Update();
    void Think();
    void Visible();

	void SetPos(float x, float z) { x_ = x; z_ = z; }

    // 目的地を取得（移動用コンポーネントが参照する）
    VECTOR GetTargetPosition() const { return targetPos_; }

    //透明時間
    float GetVisibleTime() const { return visibleTimer_; }
	void SetVisibleTime(float time) { visibleTimer_ = time; }

    //鬼の位置
    void SetEnemyPositions(const std::vector<VECTOR>& positions) {
        enemyPositions_ = positions;
    }

private:
    float CalculateTileScore(int tw, int td, const std::vector<VECTOR>& enemyPos);

    int lastStepTileW_; // 前回いたタイルのW座標
    int lastStepTileD_; // 前回いたタイルのD座標
    float visibleTimer_; // 姿が見えている残り時間

};

