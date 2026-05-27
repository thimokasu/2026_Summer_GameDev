#pragma once
#pragma warning(disable:4996) 
#include <DxLib.h>



class GameMessageUI
{
public:
	
	static constexpr int FontSize = 100;
	static constexpr int EdgeSize = 4;
	static constexpr int ANIM_MAX_TIME = 3;

	static constexpr const char* StrStart = "START!";
	static constexpr const char* StrFinish = "FINISH!";
	static constexpr const char* StrExplain = "FIND　J!!";
	static constexpr const char* StrNone = "";

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

	void Update(void);

	void TextAnim(void);

	// 描画処理
	void Draw(int screenWidth, int screenHeight);

	MessageState GetStateUI(void) const { return currentState_; }

private:

	int fontHandle_ = -1;
	MessageState currentState_ = MessageState::None;

	unsigned int textColor_ = 0;
	unsigned int edgeColor_ = 0;

	enum class AnimPhase {
		FadeIn,   // 大きくなる期間
		Stay,     // 最大サイズで維持する期間
		FadeOut,  // 小さくなって消える期間
	};
	AnimPhase animPhase_ = AnimPhase::FadeIn;

	float animTime_;
	float sizeY_;
	float sizeX_;

};