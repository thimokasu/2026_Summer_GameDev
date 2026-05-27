#include "GameMessageUI.h"

GameMessageUI::GameMessageUI()
{
	textColor_ = GetColor(255, 255, 255); // îíï∂éö
	edgeColor_ = GetColor(0, 0, 0);       // çï
}

void GameMessageUI::Initialize()
{
	if (fontHandle_ == -1)
	{
		fontHandle_ = CreateFontToHandle("Arial", FontSize, 6, DX_FONTTYPE_ANTIALIASING_EDGE, -1, EdgeSize);
	}
}

void GameMessageUI::SetState(MessageState state)
{
	currentState_ = state;

	switch (currentState_)
	{
	case MessageState::Start:
		textColor_ = GetColor(0, 200, 255);   // êÖêF
		edgeColor_ = GetColor(255, 255, 255); // îí
		break;

	case MessageState::Finish:
		textColor_ = GetColor(255, 215, 0);   // â©êF
		edgeColor_ = GetColor(255, 255, 255); // îí
		break;

	case MessageState::Explain:
		textColor_ = GetColor(255, 255, 255); // îí
		edgeColor_ = GetColor(0, 0, 0);       // çï
		break;

	default:
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
	default: return;
	}

	if (targetStr == nullptr) return;

	
	int stringWidth = 0;
	int stringHeight = 0;
	int lineCount = 0;
	GetDrawStringSizeToHandle(&stringWidth, &stringHeight, &lineCount, targetStr, (int)strlen(targetStr), fontHandle_);


	int drawX = (screenWidth - stringWidth) / 2;
	int drawY = (screenHeight - stringHeight) / 2;

	
	DrawRotaStringToHandle(
		drawX, drawY,
		1.0, 1.0,           
		0.0, 0.0,           
		0.0,              
		textColor_,       
		fontHandle_,       
		edgeColor_,        
		FALSE,              
		targetStr           
	);
}