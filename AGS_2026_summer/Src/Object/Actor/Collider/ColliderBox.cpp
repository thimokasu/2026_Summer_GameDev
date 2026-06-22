#include "ColliderBox.h"

ColliderBox::ColliderBox(ColliderInfo& info, VECTOR& halfSize, ActorBase& actor)
	: ColliderBase(info, actor), halfSize_(halfSize)
{
}

ColliderBox::ColliderBox(ColliderInfo& info, VECTOR& halfSize, ActorBase& actor, int debugColor)
	: ColliderBase(info, actor), halfSize_(halfSize)
{
	info.debugColor_ = debugColor;
}

VECTOR ColliderBox::Local2World(const VECTOR& localPos) const
{
	VECTOR center = GetRotPos(colliderInfo_.localPos_);

	return VAdd(
		center,
		VAdd(
			VAdd(
				VScale(GetAxisX(), localPos.x),
				VScale(GetAxisY(), localPos.y)),
			VScale(GetAxisZ(), localPos.z)
		)
	);
}

VECTOR ColliderBox::World2Local(const VECTOR& worldPos) const
{
	// ワールド座標から中心座標を引いて、ローカル軸に投影する
	VECTOR center = GetRotPos(colliderInfo_.localPos_);
	// ワールド座標から中心座標を引く
	VECTOR dir = VSub(worldPos, center);
	// ローカル軸に投影する
	return VGet(
		VDot(dir, GetAxisX()),
		VDot(dir, GetAxisY()),
		VDot(dir, GetAxisZ())
	);
}

VECTOR ColliderBox::GetVertexPos(int index) const
{
	// 中心座標
	VECTOR center = GetRotPos(colliderInfo_.localPos_);

	// 統一されたゲッターから回転済みのワールド軸を取得
	VECTOR axisX = GetAxisX();
	VECTOR axisY = GetAxisY();
	VECTOR axisZ = GetAxisZ();

	// 8頂点の配列
	VECTOR hx = VScale(axisX, halfSize_.x);
	VECTOR hy = VScale(axisY, halfSize_.y);
	VECTOR hz = VScale(axisZ, halfSize_.z);

	VECTOR v[8] =
	{
		VAdd(center,VAdd(VAdd(hx,hy),hz)),              // +x,+y,+z
		VAdd(center,VAdd(VAdd(hx,hy),VScale(hz,-1.0f))),   // +x,+y,-z
		VAdd(center,VAdd(VAdd(hx,VScale(hy,-1.0f)),hz)),   // +x,-y,+z
		VAdd(center,VAdd(VAdd(hx,VScale(hy,-1.0f)),VScale(hz,-1.0f))), // +x,-y,-z
		VAdd(center,VAdd(VAdd(VScale(hx,-1.0f),hy),hz)),  // -x,+y,+z
		VAdd(center,VAdd(VAdd(VScale(hx,-1.0f),hy),VScale(hz,-1.0f))), // -x,+y,-z
		VAdd(center,VAdd(VAdd(VScale(hx,-1.0f),VScale(hy,-1.0f)),hz)), // -x,-y,+z
		VAdd(center,VAdd(VAdd(VScale(hx,-1.0f),VScale(hy,-1.0f)),VScale(hz,-1.0f))) // -x,-y,-z
	};

	if (index < 0 || index > 7) return center; // 範囲外なら中心返す
	return v[index];
}

void ColliderBox::DrawDebug(int color)
{
	// 中心座標
	VECTOR center = GetRotPos(colliderInfo_.localPos_);

	// 正しく回転している8頂点を取得
	VECTOR v[8];
	for (int i = 0; i < 8; ++i)
	{
		v[i] = GetVertexPos(i);
	}

	// 1. 先に中の塗りつぶし（ソリッド）を描画
	// 箱の6面を構成する12個の三角形の頂点インデックスの組み合わせ
	// 面が裏返って消えないように表面の向き（時計回り）に結ぶ
	int idx[12][3] = {
		{0, 1, 2}, {3, 2, 1}, // 前面 (+X側)
		{4, 6, 5}, {7, 5, 6}, // 背面 (-X側)
		{0, 2, 4}, {6, 4, 2}, // 左面 (-Y側)
		{1, 5, 3}, {7, 3, 5}, // 右面 (+Y側)
		{0, 4, 1}, {5, 1, 4}, // 上面 (+Z側)
		{2, 3, 6}, {7, 6, 3}  // 下面 (-Z側)
	};

	// 透過させて奥を少し見えやすくしたい場合は、事前に中身のカラーを加工すると見やすくなります
	for (int i = 0; i < 12; i++)
	{
		// 3D空間上に塗りつぶし三角形を描画 (最後の引数をTRUEにするとテクスチャなしの単色塗り潰し)
		DrawTriangle3D(v[idx[i][0]], v[idx[i][1]], v[idx[i][2]], color, TRUE);
	}

	// 2. 輪郭がぼやけないように、上からワイヤーフレーム（12辺）を描画
	unsigned char edges[12][2] =
	{
		{0,1},{0,2},{0,4},
		{1,3},{1,5},
		{2,3},{2,6},
		{3,7},
		{4,5},{4,6},
		{5,7},
		{6,7}
	};
	// 輪郭線は少し目立つ色（あるいは黒や白など）にするか、同じcolorでもポリゴンよりくっきり見えます
	for (int i = 0; i < 12; i++)
	{
		DrawLine3D(v[edges[i][0]], v[edges[i][1]], GetColor(255, 255, 255)); // 例として白線
	}

	// 中心点
	DrawSphere3D(center, 2.0f, 8, color, color, false);
}