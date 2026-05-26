#pragma once
#include "GameMessageUI.h"
#include "Timer.h"

class UIManager
{
	public:
	UIManager();
	~UIManager() = default;
	void Initialize();
	void Update();
	void Draw(void);
	void Release(void);
	void SetMessageState(GameMessageUI::MessageState state)
	{
		message_ = state;

		gameMessageUI_.SetState(state);
	}

private:

	GameMessageUI gameMessageUI_;
	Timer timer_;

	//メッセージの切り替え
	GameMessageUI::MessageState message_;

};

