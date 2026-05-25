#include "FindingJCPU.h"
#include <cmath> 
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../../../Scene/GameSelect/GameKind.h"
#include"../../../Collider/ColliderBase.h"
#include"../../../Collider/ColliderCapsule.h"
#include"../../../Manager/ActorManager.h"

FindingJCPU::FindingJCPU(ActorManager& actMana)
    : actorManager_(actMana)
{

}

FindingJCPU::~FindingJCPU(void)
{
}

void FindingJCPU::SubLoad(void)
{
}

void FindingJCPU::SubInit(void)
{
	entityKind_ = EntityKind::FINDINGJ_CPU;
	rigidBody_.SetBodyType(RigidBody::BodyType::DYNAMIC);
	rigidBody_.SetUseGravity(true);
	rigidBody_.SetMass(1);
	rigidBody_.SetMoveSpeed(0.25f);
	trans_.pos = { 25,25,25 };
}

void FindingJCPU::SubUpdate(void)
{
	timer_ -= SceneManager::GetInstance().GetDeltaTime();
	if (timer_ <= 0.0f)
	{
		Think();
		timer_ = DecisionInterval;
	}
	Visible();
	if(visibleTimer_ > 0.0f)
	{
		visibleTimer_ -= SceneManager::GetInstance().GetDeltaTime();
	}
	Move();
}

void FindingJCPU::SubDraw(void)
{
	if(visibleTimer_ > 0.0f)
	{
		isDraw_ = true;
	}
	else
	{
		isDraw_ = false;
	}
	DrawSphere3D(targetPos_, 10.0f, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
	DrawFormatString(200, 50, GetColor(255, 255, 255), "CPU Target: (%.1f, %.1f, %.1f)", targetPos_.x, targetPos_.y, targetPos_.z);
}

void FindingJCPU::SubRelease(void)
{
}

void FindingJCPU::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::CAPSULE;
	info.layer_ = ColliderLayer::ACTOR;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR,Layer::STAGE });
	float radius = 5.0f;
	VECTOR localPosTop = VGet(0.0f, 10.0f, 0.0f);
	VECTOR localPosDown = VGet(0.0f, -10.0f, 0.0f);
	std::unique_ptr<ColliderCapsule>collider =
		std::make_unique<ColliderCapsule>(info, radius, localPosTop, localPosDown, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
}


void FindingJCPU::Move(void)
{
	VECTOR moveVec = VSub(targetPos_, trans_.pos);

	moveVec.y = 0.0f;

	if (VSize(moveVec) > 0.05f) 
	{
		moveVec = VNorm(moveVec);
		rigidBody_.AddForce(VScale(moveVec, rigidBody_.GetMoveSpeed()));
	}
}


void FindingJCPU::Think(void)
{
	// 1. 現在の座標から、一番近いブロックのインデックスを「四捨五入」で出す
	int curW = static_cast<int>(std::round(trans_.pos.x / TileSize));
	int curD = static_cast<int>(std::round(trans_.pos.z / TileSize));

	// 安全対策：配列の範囲内に収める
	if (curW < 0) curW = 0; if (curW >= W) curW = W - 1;
	if (curD < 0) curD = 0; if (curD >= D) curD = D - 1;

	// 敵（プレイヤー）の座標リストを取得
	enemyPositions_.clear();
	auto enemy = actorManager_.FindActorsByKind(EntityKind::PLAYER);
	for (auto& e : enemy)
	{
		enemyPositions_.push_back(e->GetTransform().pos);
	}

	// 初期スコアを最悪（最大）の値にしておく
	float bestScore = 1000000.0f;

	// 動ける場所が1つもない時のためのバックアップ（現在の自分のマスの真ん中）
	VECTOR currentCenter = VGet(curW * TileSize , trans_.pos.y, curD * TileSize);
	VECTOR bestTilePos = currentCenter;

	// 前後左右の4方向
	int dirs[4][2] = {
		{ 1,  0}, // 右
		{-1,  0}, // 左
		{ 0,  1}, // 上（奥）
		{ 0, -1}  // 下（手前）
	};

	for (int i = 0; i < 4; ++i)
	{
		int nextW = curW + dirs[i][0];
		int nextD = curD + dirs[i][1];

		// 範囲外ならパス
		if (nextW < 0 || nextW >= W || nextD < 0 || nextD >= D) continue;

		// 壁ブロックの判定（高さ1がNone以外なら壁なので「絶対に」選択肢から外す）
		bool isWall = false;
		if (stageNum_ == static_cast<int>(FourPlayer::FindingJ::Stage::Stage1))
		{
			if (Stage1::stage[1][nextD][nextW] != StageLayout::None) isWall = true;
		}
		else if (stageNum_ == static_cast<int>(FourPlayer::FindingJ::Stage::Stage2))
		{
			if (Stage2::stage[1][nextD][nextW] != StageLayout::None) isWall = true;
		}
		else if (stageNum_ == static_cast<int>(FourPlayer::FindingJ::Stage::Stage3))
		{
			if (Stage3::stage[1][nextD][nextW] != StageLayout::None) isWall = true;
		}

		if (isWall) continue; // 壁なら、スコア計算すらさせずに完全除外！

		// ここに到達したということは「歩ける床」である。
		// その床のスコア（プレイヤーとの近さ）を計算
		float score = CalculateTileScore(nextW, nextD, enemyPositions_);

		// 【ここがポイント！】
		// 歩ける床の中で、一番スコアが低い（＝プレイヤーから一番遠い）マスを純粋に比較して選ぶ
		if (score < bestScore)
		{
			bestScore = score;
			bestTilePos = VGet(nextW * TileSize , trans_.pos.y, nextD * TileSize);
		}
	}

	// --- 【超重要】袋小路での立ち往生を絶対にぶっ壊す処理 ---
	// もし「どのマスに進んでも今よりプレイヤーに近づいちゃうから、動きたくない！」
	// となって bestTilePos が自分の足元（currentCenter）から変わらなかった場合、
	// 「背に腹は代えられないから、プレイヤーに近づいてでも、とりあえず進める床に突っ込め！」と強制決定する。
	if (bestTilePos.x == currentCenter.x && bestTilePos.z == currentCenter.z)
	{
		for (int i = 0; i < 4; ++i)
		{
			int nextW = curW + dirs[i][0];
			int nextD = curD + dirs[i][1];
			if (nextW < 0 || nextW >= W || nextD < 0 || nextD >= D) continue;

			bool isWall = false;
			if (stageNum_ == static_cast<int>(FourPlayer::FindingJ::Stage::Stage1) && Stage1::stage[1][nextD][nextW] != StageLayout::None) isWall = true;
			if (stageNum_ == static_cast<int>(FourPlayer::FindingJ::Stage::Stage2) && Stage2::stage[1][nextD][nextW] != StageLayout::None) isWall = true;
			if (stageNum_ == static_cast<int>(FourPlayer::FindingJ::Stage::Stage3) && Stage3::stage[1][nextD][nextW] != StageLayout::None) isWall = true;

			if (!isWall)
			{
				// 壁じゃない床を見つけたら、最悪の方向（プレイヤー側）だとしても強制的にそこをターゲットにして脱出する！
				bestTilePos = VGet(nextW * TileSize , trans_.pos.y, nextD * TileSize);
				break;
			}
		}
	}

	targetPos_ = bestTilePos;
}

void FindingJCPU::Visible(void)
{
	int curW = static_cast<int>(trans_.pos.x / TileSize);
	int curD = static_cast<int>(trans_.pos.z / TileSize);

	if (curW != lastStepTileW_ || curD != lastStepTileD_)
	{
lastStepTileW_ = curW;
		lastStepTileD_ = curD;
	}
}

float FindingJCPU::CalculateTileScore(int tw, int td, const std::vector<VECTOR>& enemyPos)
{
	float score = 0.0f;
	// マスの中心座標を計算（+ TileSize / 2.0f を足すとより正確になります）
	VECTOR tilePos = VGet(tw * TileSize + (TileSize / 2.0f), 0.0f, td * TileSize + (TileSize / 2.0f));

	// 敵（プレイヤー）との距離スコア
	for (const auto& e : enemyPos)
	{
		// 完全に水平面（X, Z）だけで距離を計算する（念のためYを潰す）
		VECTOR p1 = tilePos; p1.y = 0.0f;
		VECTOR p2 = e;       p2.y = 0.0f;
		float dist = VSize(VSub(p1, p2));

		// 【修正ポイント】反比例をやめ、直線的なマイナス評価にする
		// プレイヤーに近づくほど（distが小さいほど）全体のscoreが高くなり（＝選ばれにくくなり）、
		// 遠ざかるほどscoreが低くなる（＝選ばれやすくなる）
		// マップの最大対角線より少し大きい値（例: 2000.0f）から引く
		score += (2000.0f - dist);
	}

	// 反応ブロック（居場所がばれる床）ペナルティ
	if (stageNum_ == static_cast<int>(FourPlayer::FindingJ::Stage::Stage1))
	{
		if (Stage1::stage[0][td][tw] == StageLayout::ReactionBlock)
		{
			score += ReactionBlockPenalty;
		}
	}
	else if (stageNum_ == static_cast<int>(FourPlayer::FindingJ::Stage::Stage2))
	{
		if (Stage2::stage[0][td][tw] == StageLayout::ReactionBlock)
		{
			score += ReactionBlockPenalty;
		}
	}
	else if (stageNum_ == static_cast<int>(FourPlayer::FindingJ::Stage::Stage3))
	{
		if (Stage3::stage[0][td][tw] == StageLayout::ReactionBlock)
		{
			score += ReactionBlockPenalty;
		}
	}

	return score;
}
