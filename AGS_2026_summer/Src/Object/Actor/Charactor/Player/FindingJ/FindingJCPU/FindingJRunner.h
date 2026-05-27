#pragma once
#include"../../../CharactorBase.h"
#include"../../../../Stage/FindingJ/StageLayout.h"
class ActorManager;

class FindingJRunner :
    public CharactorBase
{   
public:
    enum class AIState
    {
		CHASER, // 追いかける
		RUNNER, // 逃げる
    };

	static constexpr float DecisionInterval = 0.01f; // 思考する間隔
    static constexpr float ReactionBlockPenalty = 5.0f;

    FindingJRunner(ActorManager&actMana);
    virtual ~FindingJRunner(void);

    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
	void InitCollider(void) override;

    void SetStageNum(int sNum) { stageNum_ = sNum; }
	void SetAIRunner(void) { aiState_ = AIState::RUNNER; }
	void SetAIChaser(void) { aiState_ = AIState::CHASER; }

	// 敵の位置設定
    void SetEnemyPositions(const std::vector<VECTOR>&positions)
	{
		enemyPositions_ = positions;
	}

private:
#pragma region  変数

	VECTOR targetPos_; // 目標位置
	std::vector<VECTOR>enemyPositions_;// 敵の位置
    ActorManager& actorManager_;
    int lastStepTileW_; // 前回いたタイルのW座標
    int lastStepTileD_; // 前回いたタイルのD座標
    float visibleTimer_; // 姿が見えている残り時間
    float timer_ = 0.0f; 
    int stageNum_;
	AIState aiState_ = AIState::CHASER; // 初期状態は追いかける
#pragma endregion

#pragma region 関数
	void Think(void); // 思考
    void Visible(void);
	void MoveToTarget(void);
#pragma endregion

};

