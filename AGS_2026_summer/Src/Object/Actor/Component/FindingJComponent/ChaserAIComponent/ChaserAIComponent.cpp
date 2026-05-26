#include "ChaserAIComponent.h"


void ChaserAIComponent::UpdateAI()
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

void ChaserAIComponent::UpdatePlayer()
{

}

void ChaserAIComponent::WanderBehavior()
{
	// 現在のタイルインデックスを算出
	int curW = static_cast<int>(x_ / TileSize);
	int curD = static_cast<int>(z_ / TileSize);

	std::vector<VECTOR> selectablePositions;

	for (int dw = -1; dw <= 1; ++dw) {
		for (int dd = -1; dd <= 1; ++dd) {
			int nextW = curW + dw;
			int nextD = curD + dd;

			// 範囲外チェック
			if (nextW < 0 || nextW >= W || nextD < 0 || nextD >= D) continue;

			// 高さ1が壁（None以外）なら通れない
			if (Stage1::stage[1][nextD][nextW] != StageLayout::None) continue;

			// 自分のいる場所（足元）ならスキップ
			if (dw == 0 && dd == 0) continue;

			// 一つ前のマス（今来た道）ならスキップ
			if (nextW == prevW_ && nextD == prevD_) continue;

			// 条件に合うマスの中心座標をリストに追加していく
			VECTOR moveTilePos = VGet(nextW * TileSize + (TileSize / 2.0f), 0, nextD * TileSize + (TileSize / 2.0f));
			selectablePositions.push_back(moveTilePos);
		}
	}

	//if (selectablePositions.empty() && (prevW_ != -1 && prevD_ != -1))
	//{
	//	
	//	VECTOR backTilePos = VGet(prevW_ * TileSize + (TileSize / 2.0f), 0, prevD_ * TileSize + (TileSize / 2.0f));
	//	selectablePositions.push_back(backTilePos);
	//}

	// 候補リストからランダムに目的地を選ぶ
	if (!selectablePositions.empty())
	{
		int randIndex = DxLib::GetRand(static_cast<int>(selectablePositions.size()) - 1);

		if (selectablePositions[randIndex].x != targetPos_.x || selectablePositions[randIndex].z != targetPos_.z)
		{
			prevW_ = curW;
			prevD_ = curD;
		}

		// 目的地を決定
		targetPos_ = selectablePositions[randIndex];
		selectablePositions.clear();
	}
}