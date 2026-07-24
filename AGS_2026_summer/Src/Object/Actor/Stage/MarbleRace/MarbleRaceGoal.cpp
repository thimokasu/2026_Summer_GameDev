#include "MarbleRaceGoal.h"
#include"../../Collider/ColliderBase.h"
#include"../../Collider/ColliderBox.h"

void MarbleRaceGoal::SubInit(void)
{
trans_.pos = VGet(0, 20, 360);
}

void MarbleRaceGoal::SubLoad(void)
{
}

void MarbleRaceGoal::InitRigidBody(void)
{
	rigidBody_.SetBodyType(RigidBody::BodyType::STATIC);
}

void MarbleRaceGoal::InitCollider(void)
{
	ColliderInfo info;
	info.shape_ = ColliderShape::BOX;
	info.layer_ = ColliderLayer::STAGE;
	info.mask_ = ColliderBase::SetMask({ Layer::ACTOR });
	info.entityKind_ = EntityKind::MARBLE_GOAL;
	info.isTrigger_ = true;
	info.debugColor_ = GetColor(0, 0, 0);
	
	VECTOR halfSize = VGet(100, 10, 1);
	std::unique_ptr<ColliderBox>collider =
		std::make_unique<ColliderBox>(info, halfSize, *this);
	ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));

	// テープの全体サイズ
	float totalWidth = 200.0f; // x: -100 ～ +100
	float totalHeight = 20.0f; // y: -10 ～ +10 (halfSize.y = 10 の場合)

	// 分割数（横と縦）
	int tileCountX = 20; // 横に20個
	int tileCountY = 2;  // 縦に2個（上下半分に割る）

	float tileWidth = totalWidth / tileCountX;   // 1個あたりの幅 (10.0f)
	float tileHeight = totalHeight / tileCountY; // 1個あたりの高さ (10.0f)

	// 各タイルの半サイズ
	VECTOR tileHalfSize = VGet(tileWidth * 0.5f, tileHeight * 0.5f, 1.0f);

	for (int y = 0; y < tileCountY; ++y)
	{
		for (int x = 0; x < tileCountX; ++x)
		{
			ColliderInfo info;
			info.shape_ = ColliderShape::BOX;
			info.layer_ = ColliderLayer::NONE;
			info.mask_ = ColliderBase::SetMask({  });
			info.entityKind_ = EntityKind::MARBLE_GOAL;
			info.isTrigger_ = true;

			// 市松模様（チェッカー柄）になるように、x と y のインデックスの合計が偶数か奇数かで白黒を切り替える
			if ((x + y) % 2 == 0) {
				info.debugColor_ = GetColor(255, 255, 255); // 白
			}
			else {
				info.debugColor_ = GetColor(0, 0, 0);       // 黒
			}

			// 各タイルのローカル座標（中心基準）を計算
			float localX = -totalWidth * 0.5f + tileWidth * 0.5f + (x * tileWidth);
			float localY = -totalHeight * 0.5f + tileHeight * 0.5f + (y * tileHeight);
			info.localPos_ = VGet(localX, localY, 0.0f);

			// 小さなColliderBoxを作成して登録
			auto collider = std::make_unique<ColliderBox>(info, tileHalfSize, *this);
			ownColliders_.emplace(static_cast<int>(info.shape_), std::move(collider));
		}
	}
}
