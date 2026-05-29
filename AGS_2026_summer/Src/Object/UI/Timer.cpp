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
	clockHandle_ = LoadGraph("Data/Image/Clock.png");
	size_ = 0.15f;
	bgColor_ = IntVector3(0, 0, 0);
}

void Timer::Update()
{
	time_ -= SceneManager::GetInstance().GetDeltaTime();

	if (time_ <= 0.9f)
	{
		time_ = 0.0f;
		//タイムオーバー判定
		if (timeUpCollback_)
		{
			timeUpCollback_();
		}
	}
}

void Timer::Draw(int x, int y)
{

	static int fontHandle = -1;
	if (fontHandle == -1)
	{
		fontHandle = CreateFontToHandle("Arial", 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 2);
	}


	unsigned int white = GetColor(255, 255, 255);

	int width = 240;
	int height = 80;

	Vector2 pos(x - width, y);

	// 基本の拡大率
	float scale = 0.15f;

	
	if (time_ <= 6.0f && time_ > 0.0f)
	{
		bgColor_ = { 220, 0, 0 };

		

		float fract = time_ - std::floor(time_);

		if (fract > 0.7f)
		{
			float wave = std::sin((fract - 0.7f) / 0.3f * DX_PI_F);

			scale = 0.15f + wave * 0.03f;
		}
		else
		{
			scale = 0.15f;
		}
	}
	else
	{
		bgColor_ = { 0, 0, 0 };
	}

	SetDrawBright(bgColor_.x, bgColor_.y, bgColor_.z);
	// 縁取り
	DrawRotaGraph(pos.x+ width/2.5, pos.y+ height/1.8, scale, 0.0, BGHandle_, TRUE);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	// 白い背景
	DrawRotaGraph(pos.x + width / 2.5, pos.y + height / 1.8, scale, 0.0, IconHandle_, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(pos.x + 10, pos.y + height / 1.8, scale - 0.09f, 0.0, clockHandle_, TRUE);

	char timeString[32];
	sprintf_s(timeString, "%d", static_cast<int>(time_)); 

//	DrawStringToHandle(pos.x + 110, pos.y + 10, timeString, black, fontHandle, white);

	int textX = pos.x + 110;
	int textY = pos.y + 10;

	double textScale = static_cast<double>(scale * 6.6f);

	unsigned int fontColor = time_ <= 6.0f ? GetColor(220, 0, 0) : GetColor(0, 0, 0);

	DrawRotaStringToHandle(
		textX, textY,
		textScale, textScale,
		0.0, 0.0,
		0.0,
		fontColor,
		fontHandle,
		white,
		FALSE,
		timeString
	);
}