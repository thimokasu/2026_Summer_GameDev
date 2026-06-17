#include "FindingJChaser.h"
#include"../../../Stage/FindingJ/StageLayout.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
FindingJChaser::FindingJChaser(void)
{
}

FindingJChaser::~FindingJChaser(void)
{
}

void FindingJChaser::SubLoad(void)
{
}

void FindingJChaser::SubInit(void)
{
	entityKind_ = EntityKind::FINDINGJ_CPU;
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(100);
	rigidBody_.SetMoveSpeed(0.5f);
	trans_.pos = VGet(100.0f, 40.0f, 100.0f);
}

void FindingJChaser::SubUpdate(void)
{
	switch (role_)
	{
	case FindingJChaser::ChaserRole::Wander:
		WanderBehavior();
		break;
	case FindingJChaser::ChaserRole::Chaser:
		break;
	case FindingJChaser::ChaserRole::Blocker:
		break;
	}
}

void FindingJChaser::SubDraw(void)
{
}

void FindingJChaser::SubRelease(void)
{
}

void FindingJChaser::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	float radius = 10.0f;
	VECTOR localPosTop = VGet(0.0f, 10.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, -10.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}

void FindingJChaser::WanderBehavior()
{
	// 現在のタイルインデックスを算出
	int curW = static_cast<int>(trans_.pos.x / TileSize);
	int curD = static_cast<int>(trans_.pos.z / TileSize);

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
