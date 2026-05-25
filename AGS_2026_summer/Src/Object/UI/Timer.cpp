#include "Timer.h"
#include "../../Manager/Game/SceneManager.h"
#include <DxLib.h>
#include "../../Common/Vector2.h"
#include <cmath>

Timer::Timer()
{
	time_ = 20.0f;
	BGHandle_ = LoadGraph("Data/Image/TimerBG.png");
	IconHandle_ = LoadGraph("Data/Image/TimerIcon.png");
	size_ = 0.15f;

}

void Timer::Update()
{
	time_ -= SceneManager::GetInstance().GetDeltaTime();
}

void Timer::Draw(int x, int y)
{

	static int fontHandle = -1;
	if (fontHandle == -1)
	{
		fontHandle = CreateFontToHandle("Arial", 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 2);
	}

	// 各種カラー設定
	unsigned int white = GetColor(255, 255, 255);
	unsigned int black = GetColor(0, 0, 0);
	unsigned int red = GetColor(220, 0, 0);

	int width = 240;
	int height = 80;

	Vector2 pos(x - width, y);

	// カプセルの描画
	int r = height / 2;

	// 基本の拡大率（通常時は 1.0f）
	float scale = 1.0f;

	
	if (time_ <= 5.0f && time_ > 0.0f)
	{
		//edgeColor = DxLib::GetColor(255, 0, 0); // フチを赤にする

		// アニメーション用の時間を進める（60FPS想定で、毎フレーム適度なスピードで加算）
		animationTimer_ += 0.15f;

		// サイン波を使って、1.0f ? 1.15f の間でサイズを滑らかに変動させる
		// std::sin は -1.0 ? 1.0 を返すので、abs（絶対値）を取ることで
		// 「小さくなりすぎず、元のサイズから周期的に大きくなる」動き（鼓動）を作れます
		scale = 0.15f + std::abs(std::sin(animationTimer_)) * 0.05f;
	}
	else
	{
		animationTimer_ = 0.0f; // 5秒より上ならカウンターをリセット
	}

	SetDrawBright(0, 0, 0);
	// 縁取り
	DrawRotaGraph(pos.x+ width/2.5, pos.y+ height/1.8, scale, 0.0, BGHandle_, TRUE);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	// 白い背景
	DrawRotaGraph(pos.x + width / 2.5, pos.y + height / 1.8, scale, 0.0, IconHandle_, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	

	//時計アイコン
	int iconCenterX = pos.x + 45;
	int iconCenterY = pos.y + (height / 2);
	int iconRadius = 20;

	// 時計の丸枠
	DrawCircle(iconCenterX, iconCenterY, iconRadius, black, FALSE, 3);
	// 時計の針
	DrawLine(iconCenterX, iconCenterY, iconCenterX, iconCenterY - 12, black, 3);
	DrawLine(iconCenterX, iconCenterY, iconCenterX + 10, iconCenterY, black, 3);

	char timeString[32];
	sprintf_s(timeString, "%d", static_cast<int>(time_)); 

	DrawStringToHandle(pos.x + 90, pos.y + 10, timeString, black, fontHandle, white);
}