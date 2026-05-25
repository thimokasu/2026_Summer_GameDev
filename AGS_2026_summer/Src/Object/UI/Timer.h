#pragma once
#include "../../Common/Vector2.h"

class Timer
{
public:


	Timer();
	~Timer() = default;
	void Update();
	float GetTime() const { return time_; }
	void Reset() { time_ = 0.0f; }
	void Draw(int x, int y);

private:

	float time_;
	int BGHandle_;
	int IconHandle_;
	float size_;

	
	float animationTimer_ = 0.0f; // サイズ変動アニメーション用の時間カウンタ


};

