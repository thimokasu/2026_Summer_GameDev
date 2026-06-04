#pragma once
#include <string>
#include <array>


enum SOUND_TYPE
{
   BGM,
   ALERT,
    MAX
};

class SE
{
public:

	static constexpr int INVALID_HANDLE = -1;

	static SE& GetInstance();

	void Load(SOUND_TYPE type, const std::string& filename);
	void Play(SOUND_TYPE type,bool isLoop=false);
	void Stop(SOUND_TYPE type);
	void SetVolume(SOUND_TYPE type, int volume);
	bool IsEnd(SOUND_TYPE type);
	void Release();

private:

	SE(); 
	~SE();
	SE(const SE&) = delete;
	SE& operator=(const SE&) = delete;

	std::array<int, static_cast<int>(SOUND_TYPE::MAX)> handles_;

};

