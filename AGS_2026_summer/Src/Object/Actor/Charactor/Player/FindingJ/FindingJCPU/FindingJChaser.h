#pragma once
#include"../../../CharactorBase.h"

class FindingJChaser :
    public CharactorBase
{
    public:

        enum class ChaserRole
        {
            Wander,   // 徘徊
            Chaser,   // 突撃役
            Blocker,  // 遮断役
        };

    FindingJChaser(void);
    virtual ~FindingJChaser(void);
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
	void InitCollider(void) override;

    // 移動方向を定義する定数ベクトル（上下左右）
    static constexpr int DIR_X[4] = { 0, 0, -1, 1 };
    static constexpr int DIR_D[4] = { -1, 1, 0, 0 };
private:
    void WanderBehavior();



    ChaserRole role_ = ChaserRole::Wander;
    VECTOR targetPos_;

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

