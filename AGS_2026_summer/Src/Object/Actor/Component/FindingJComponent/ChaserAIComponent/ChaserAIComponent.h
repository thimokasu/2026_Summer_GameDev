#include "../../ComponentBase.h"
#include "../../../Stage/FindingJ/StageLayout.h"
#include "DxLib.h"
#include <vector>


enum class ChaserRole
{
	Wander,   // 徘徊
	Chaser,   // 突撃役
	Blocker,  // 遮断役
};

class ChaserAIComponent : public ComponentBase
{
public:
	ChaserAIComponent()
		: ComponentBase()
		, role_(ChaserRole::Wander)
		, targetPos_(0.0f, 0.0f, 0.0f)
		, isCPU_(true) // デフォルトはCPU
	{
	}

	void Update()
	{
		if (isCPU_)
		{
			UpdateAI(); // CPUとしての移動ロジック
		}
		else
		{
			UpdatePlayer(); // プレイヤー入力による移動ロジック
		}
	}

	// マネージャー（司令塔）から命令をセットされる関数
	void SetCommand(ChaserRole role, const VECTOR& targetPos)
	{
		role_ = role;
		targetPos_ = targetPos;
	}

	// ゲッター群
	ChaserRole GetRole() const { return role_; }
	VECTOR GetTargetPosition() const { return targetPos_; }
	bool IsCPU() const { return isCPU_; }

	// プレイヤー操作かCPU操作かを切り替える
	void SetAsPlayer(bool isPlayer) { isCPU_ = !isPlayer; }
	void SetPos(float x, float z) { x_ = x; z_ = z; }

public:

	// 移動方向を定義する定数ベクトル（上下左右）
	static constexpr int DIR_X[4] = { 0, 0, -1, 1 };
	static constexpr int DIR_D[4] = { -1, 1, 0, 0 };

private:
	void UpdateAI();
	void UpdatePlayer();
	void WanderBehavior();

private:
	ChaserRole role_ = ChaserRole::Wander;
	VECTOR targetPos_; 
	bool isCPU_;        // 人間かCPUかを識別するフラグ
	float x_ = 0.0f;
	float z_ = 0.0f;

	int currentDirIndex_ = 0; // 現在進んでいる方向のインデックス（0?3）
	bool isMoving_ = false;   // 次のマスへ移動中かどうかのフラグ

	// 現在地と目的地のタイルインデックス（W列、D行）
	int tileX_ = 1;
	int tileD_ = 1;
	int targetTileX_ = 1;
	int targetTileD_ = 1;
	int prevW_ = -1; // 一つ前のマス（横
	int prevD_ = -1; // 一つ前のマス（縦）
};