#pragma once
#pragma warning(disable:4996) 
#include <DxLib.h>

class GameMessageUI
{
public:
	
	static constexpr int FontSize = 100;
	static constexpr int EdgeSize = 4;

	static constexpr const char* StrStart = "START!";
	static constexpr const char* StrFinish = "FINISH!";
	static constexpr const char* StrExplain = "";

	// メッセージの状態を管理する列挙型
	enum class MessageState
	{
		None,
		Start,      // スタート表示
		Finish,     // フィニッシュ表示
		Explain     // 説明文表示
	};

public:
	GameMessageUI();
	~GameMessageUI() = default;

	void Initialize();

	// どのメッセージを表示するか切り替える
	void SetState(MessageState state);

	// 描画処理
	void Draw(int screenWidth, int screenHeight);

private:

	int fontHandle_ = -1;
	MessageState currentState_ = MessageState::None;

	unsigned int textColor_ = 0;
	unsigned int edgeColor_ = 0;
};