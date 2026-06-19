#include "SE.h"
#include <DxLib.h>

SE& SE::GetInstance(void)
{
	static SE instance; 
	return instance;
}
SE::SE()
{
	handles_.fill(-1);
}

SE::~SE(void)
{
}

void SE::Load(SOUND_TYPE type, const std::string& filename)
{
	int index = static_cast<int>(type);
	handles_[index] = LoadSoundMem(filename.c_str());

	if (handles_[index] == INVALID_HANDLE)
	{
		printfDx("SE‚Ì“Ç‚İ‚İ‚É¸”s: %s\n", filename.c_str());
	}
}

void SE::Play(SOUND_TYPE type, bool isLoop)
{
	int handle = handles_[static_cast<int>(type)];
	if (handle != INVALID_HANDLE)
	{
		PlaySoundMem(handle, DX_PLAYTYPE_BACK);
	}
}

void SE::Stop(SOUND_TYPE type)
{
	int handle = handles_[static_cast<int>(type)];
	if (handle != INVALID_HANDLE)
	{
		StopSoundMem(handle);
	}
}

void SE::SetVolume(SOUND_TYPE type, int volume)
{
	int handle = handles_[static_cast<int>(type)];
	if (handle != INVALID_HANDLE)
	{
		ChangeVolumeSoundMem(volume, handle);
	}
}

bool SE::IsEnd(SOUND_TYPE type)
{
	int handle = handles_[static_cast<int>(type)];
	if (handle != INVALID_HANDLE)
	{
		return CheckSoundMem(handle) == 0; // 0‚È‚çÄ¶’†‚Å‚Í‚È‚¢
	}
	return true; // ƒnƒ“ƒhƒ‹‚ª–³Œø‚Èê‡‚ÍÄ¶‚³‚ê‚Ä‚¢‚È‚¢‚Æ‚İ‚È‚·
}

void SE::Release()
{
	for (int& handle : handles_)
	{
		if (handle != INVALID_HANDLE)
		{
			DeleteSoundMem(handle);
			handle = INVALID_HANDLE;
		}
	}
}