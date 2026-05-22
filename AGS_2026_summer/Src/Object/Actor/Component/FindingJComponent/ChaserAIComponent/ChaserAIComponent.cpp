#include "ChaserAIComponent.h"


void ChaserController::UpdateAI()
{
	switch (role_)
	{
	case ChaserRole::Wander:
		// ランダムな隣接ノードを選んでゆっくり移動
		WanderBehavior();
		break;

	case ChaserRole::Chaser:
		// ターゲットの座標へ向けて A* で最短経路を毎フレーム（または数フレームおきに）計算して進む
		//MoveAlongPath(AStar::FindPath(position_, targetPos_));
		break;

	case ChaserRole::Blocker:
		// マネージャーから指定された「先回り交差点ノード」へ向かって A* で進む
		// 到着したらその場で待ち構える（道を塞ぐ）
		//MoveAlongPath(AStar::FindPath(position_, targetPos_));
		break;
	}
}

void ChaserController::UpdatePlayer()
{

}

void ChaserController::WanderBehavior()
{
	// 3D空間の現在座標から、現在のタイル位置を逆算（TileSize = 20）
	if (!isMoving_)
	{
		//進む方向を決める
		std::vector<int> selectableDirections;

		for (int i = 0; i < 4; ++i)
		{
			int nextX = tileX_ + DIR_X[i];
			int nextD = tileD_ + DIR_D[i];

			if (nextX >= 0 && nextX < W && nextD >= 0 && nextD < D)
			{
				if (Stage1::stage[1][nextD][nextX] == StageLayout::None)
				{
					// Uターンは、行き止まりじゃない限り避けるための判定
					int backDirIndex = currentDirIndex_ ^ 1; 
					if (i == backDirIndex && selectableDirections.size() > 0)
					{
						continue;
						}
					selectableDirections.push_back(i);
				}
			}
		}

		// 進める方向からランダムに1つ選択
		if (!selectableDirections.empty())
		{
			// 本来は乱数（GetRandなど）を使う
			int randIndex = DxLib::GetRand(static_cast<int>(selectableDirections.size()) - 1);
			currentDirIndex_ = selectableDirections[randIndex];

			targetTileX_ = tileX_ + DIR_X[currentDirIndex_];
			targetTileD_ = tileD_ + DIR_D[currentDirIndex_];
			isMoving_ = true;
		}
	}

	// 移動中の処理
	if (isMoving_)
	{
		// 目標タイルの世界座標を計算
		float worldTargetX = targetTileX_ * TileSize + (TileSize / 2.0f);
		float worldTargetZ = targetTileD_ * TileSize + (TileSize / 2.0f); // 奥行きをZとする

		
	}
}
