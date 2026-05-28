#include "UIManager.h"
#include "../../Application.h"

UIManager::UIManager()
{
	message_ = GameMessageUI::MessageState::None;
}

void UIManager::Initialize()
{

	auto onTimeUpCollback = [this]()
		{
			SetMessageState(GameMessageUI::MessageState::Finish);
		};

	timer_.SetTimeUpCollback(onTimeUpCollback);

	// ゲームメッセージUIの初期化
	gameMessageUI_.Initialize();
}

void UIManager::Update()
{
	if (gameMessageUI_.GetStateUI() == GameMessageUI::MessageState::None)
	{
		// タイマーの更新
		timer_.Update();
	}
	gameMessageUI_.Update();
}

void UIManager::Draw(void)
{
	// タイマーの描画
	timer_.Draw(Application::SCREEN_SIZE_X, 10);

	// ゲームメッセージUIの描画
	gameMessageUI_.Draw(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y);
}

void UIManager::Release(void)
{
}