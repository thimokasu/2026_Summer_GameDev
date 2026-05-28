#include "GameMessageUI.h"
#include"../../Manager/Game/SceneManager.h"
GameMessageUI::GameMessageUI()
{
	textColor_ = GetColor(255, 255, 255); // 白文字
	edgeColor_ = GetColor(0, 0, 0);       // 黒
}

void GameMessageUI::Initialize()
{
	if (fontHandle_ == -1)
	{
		fontHandle_ = CreateFontToHandle("Arial", FontSize, 6, DX_FONTTYPE_ANTIALIASING_EDGE, -1, EdgeSize);
	}
	animTime_ = 0;
	sizeY_ = 0.0;
	sizeX_ = 0.0;
}

void GameMessageUI::SetState(MessageState state)
{
	currentState_ = state;
	animTime_ = 0;
	sizeX_ = 0.0f;
	sizeY_ = 0.0f;
	animPhase_ = AnimPhase::FadeIn;
	switch (currentState_)
	{
	case MessageState::Start:
		textColor_ = GetColor(0, 200, 255);   // 水色
		edgeColor_ = GetColor(255, 255, 255); // 白
		break;

	case MessageState::Finish:
		textColor_ = GetColor(255, 215, 0);   // 黄色
		edgeColor_ = GetColor(255, 255, 255); // 白
		break;

	case MessageState::Explain:
		textColor_ = GetColor(255, 255, 255); // 白
		edgeColor_ = GetColor(0, 0, 0);       // 黒
		break;
	case MessageState::None:
		animTime_ = 0;
		sizeX_ = 0.0f;
		sizeY_ = 0.0f;
		animPhase_ = AnimPhase::FadeIn;
		break;
	default:
		break;
	}
}

void GameMessageUI::Update(void)
{
	if (currentState_ != MessageState::None)
	{
		animTime_ += SceneManager::GetInstance().GetDeltaTime();
		TextAnim();
	}
}

void GameMessageUI::TextAnim(void)
{
	static constexpr float ChangeSpeedIN = 0.02f;
	static constexpr float ChangeSpeedOut = 0.04f;
	static constexpr int   StayFrames = 2;

	//文字の拡大縮小アニメーション
	switch (animPhase_)
	{
	case AnimPhase::FadeIn:
		sizeX_ += ChangeSpeedIN;
		sizeY_ += ChangeSpeedIN;

		if (sizeX_ >= 1.0f)
		{
			sizeX_ = 1.0f;
			sizeY_ = 1.0f;
			animTime_ = 0;
			animPhase_ = AnimPhase::Stay;
		}
		break;

	case AnimPhase::Stay:
		if (animTime_ >= StayFrames)
		{
			animPhase_ = AnimPhase::FadeOut;
		}
		break;

	case AnimPhase::FadeOut:
		sizeX_ -= ChangeSpeedOut;
		sizeY_ -= ChangeSpeedOut;

		if (sizeX_ <= 0.0f)
		{
			sizeX_ = 0.0f;
			sizeY_ = 0.0f;
			//ゲーム説明の後だけスタートに切り替える
			if (currentState_ == MessageState::Explain) { SetState(MessageState::Start); return; }
			SetState(MessageState::None);
		}
		break;
	}
}

void GameMessageUI::Draw(int screenWidth, int screenHeight)
{
	if (currentState_ == MessageState::None) return;

	if (fontHandle_ == -1)
	{
		fontHandle_ = CreateFontToHandle("Arial", FontSize, 3, DX_FONTTYPE_ANTIALIASING_EDGE, -1, EdgeSize);
	}

	const char* targetStr = nullptr;

	switch (currentState_)
	{
	case MessageState::Start:   targetStr = StrStart;   break;
	case MessageState::Finish:  targetStr = StrFinish;  break;
	case MessageState::Explain: targetStr = StrExplain; break;
	case MessageState::None:  targetStr = StrNone;   break;
	default: return;
	}

	if (targetStr == nullptr) return;

	
	int stringWidth = 0;
	int stringHeight = 0;
	int lineCount = 0;
	GetDrawStringSizeToHandle(&stringWidth, &stringHeight, &lineCount, targetStr, (int)strlen(targetStr), fontHandle_);


	float cx = stringWidth / 2.0f;
	float cy = stringHeight / 2.0f;

	int drawX = screenWidth / 2;
	int drawY = screenHeight / 2;
	
	//ゲーム説明の時だけ文字の後ろに帯を出す
	if (currentState_ == MessageState::Explain)
	{
		int paddingY = 20;
		int barTop = drawY - (int)cy - paddingY;
		int barBottom = drawY + (int)cy + paddingY;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);

		DrawBox(0, barTop, screenWidth, barBottom, GetColor(0, 0, 0), TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	DrawRotaStringToHandle(
		drawX, drawY,
		sizeX_, sizeY_,
		cx, cy,
		0.0,
		textColor_,
		fontHandle_,
		edgeColor_,
		FALSE,
		targetStr
	);
}