#include "ButtonMashingPlayer.h"

#include"../../../../../Manager/Generic/KeyManager.h"


ButtonMashingPlayer::ButtonMashingPlayer(void)
{
}

ButtonMashingPlayer::~ButtonMashingPlayer(void)
{
}

void ButtonMashingPlayer::SubLoad(void)
{
}

void ButtonMashingPlayer::SubInit(void)
{
	mashCount_ = 0;
	
}

void ButtonMashingPlayer::SubUpdate(void)
{
	InputUpdate();
}

void ButtonMashingPlayer::SubDraw(void)
{
}

void ButtonMashingPlayer::SubRelease(void)
{
}

void ButtonMashingPlayer::InputUpdate(void)
{
	if (activeButton_ == Button::A)
	{
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::A).down)
		{
			mashCount_++;
		}
	}
	else if (activeButton_ == Button::B)
	{
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::B).down)
		{
			mashCount_++;
		}
	}
	else if (activeButton_ == Button::X)
	{
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::X).down)
		{
			mashCount_++;
		}
	}
	else if (activeButton_ == Button::Y)
	{
		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::Y).down)
		{
			mashCount_++;
		}
	}
}
