#pragma once
#include "../../ComponentBase.h"
#include "../../../Stage/FindingJ/StageLayout.h"
#include <vector>


class RunnerAIComponent :
    public ComponentBase
{
public:
    static constexpr float DecisionInterval = 0.15f; // 思考間隔（秒）
    static constexpr float ReactionBlockPenalty = 30.0f; // 光る床を通る際のリスク加算

private:
    float x_ = 0.0f;
    float z_ = 0.0f;
    float timer_ = 0.0f;

    VECTOR targetPos_ = VGet(0, 0, 0); 

public:
    RunnerAIComponent();
    virtual ~RunnerAIComponent() = default;

    void Update(float deltaTime);

    // 目的地を取得（移動用コンポーネントが参照する）
    VECTOR GetTargetPosition() const { return targetPos_; }

private:
    void Think();
    float CalculateTileScore(int tw, int td, const std::vector<VECTOR>& enemyPos);
};

