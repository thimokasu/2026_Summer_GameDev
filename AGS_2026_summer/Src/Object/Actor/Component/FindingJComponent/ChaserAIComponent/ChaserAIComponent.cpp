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
		Chase();
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

			// 高さ1が壁なら通れない
			if (Stage3::stage[1][nextD][nextW] != StageLayout::None) continue;

			// 自分のいる場所ならスキップ
			if (dw == 0 && dd == 0) continue;

			// 一つ前のマスならスキップ
			if (nextW == prevW_ && nextD == prevD_) continue;

			// 条件に合うマスの中心座標をリストに追加していく
			pos_ = VGet(nextW * TileSize + (TileSize / 2.0f), 0, nextD * TileSize + (TileSize / 2.0f));
			//selectablePositions.push_back(moveTilePos);
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

		if (selectablePositions[randIndex].x != pos_.x || selectablePositions[randIndex].z != pos_.z)
		{
			prevW_ = curW;
			prevD_ = curD;
		}

		// 目的地を決定
		pos_ = selectablePositions[randIndex];
		selectablePositions.clear();
	}
}

void ChaserAIComponent::Chase()
{
	/*VECTOR toTarget = VSub(pos_, pos_);

	toTarget.y = 0.0f;

	float distance = VSize()*/
}
