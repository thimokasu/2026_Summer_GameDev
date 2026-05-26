#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/IntVector3.h"
#include <functional>

using TimeUpCollback = std::function<void()>;

class Timer
{
public:


	Timer();
	~Timer() = default;
	void Update();
	float GetTime() const { return time_; }
	void Reset() { time_ = 0.0f; }
	void Draw(int x, int y);

	//タイムアップのコールバック処理
	void SetTimeUpCollback(TimeUpCollback collback)
	{
		timeUpCollback_ = collback;
	}

private:

	float time_;
	int BGHandle_;
	int IconHandle_;
	int clockHandle_;
	float size_;
	IntVector3 bgColor_;

	TimeUpCollback timeUpCollback_;


};

