#pragma once
#include "../../CharactorBase.h"
#include"../../../Stage/FindingJ/StageLayout.h"
class ActorManager;

class FindingJCPU :
    public CharactorBase
{   
public:
	static constexpr float DecisionInterval = 0.01f; // 思考する間隔
    static constexpr float ReactionBlockPenalty = 5.0f;

    FindingJCPU(ActorManager&actMana);
    virtual ~FindingJCPU(void);

    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
	void InitCollider(void) override;

    void SetStageNum(int sNum) { stageNum_ = sNum; }

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
#pragma endregion

#pragma region 関数
	void Think(void); // 思考
    void Visible(void);
	float CalculateTileScore(int tw, int td, const std::vector<VECTOR>& enemyPos); // タイルのスコア計算
    void Move(void);
#pragma endregion

};

