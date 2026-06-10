#pragma once
#include<string>

enum class GAME_KIND
{
	NONE = -1,

	// 1人用
	ONE_PLAYER = 10,
	TEST_ONE,

	//2人用
	TWO_PLAYER = 20,
	TEST_TWO,

	//3人用
	THREE_PLAYER = 30,
	TEST_THREE,
	//4人用
	FOUR_PLAYER = 40,
	TEST_FOUR,
	FINDINGJ,

};

enum class PLAY_NUM
{
	ONE_PLAYER,
	TWO_PLAYER,
	THREE_PLAYER,
	FOUR_PLAYER,
};

enum class STAGE_NUM
{
	STAGE1,
	STAGE2,
	STAGE3,
	MAX,	//最大それぞれ３ステージまで
};


struct GameInfo
{
	GAME_KIND game_;
	STAGE_NUM stage_;
	PLAY_NUM playNum_;
	std::string GetGameName(void)const;
};

inline std::string GameInfo::GetGameName(void) const
{
	switch (game_)
	{
	case GAME_KIND::NONE:
		return "None";
	case GAME_KIND::ONE_PLAYER:
		return "One Player";
	case GAME_KIND::TEST_ONE:
		return "Test One";
	case GAME_KIND::TWO_PLAYER:
		return "Two Player";
	case GAME_KIND::TEST_TWO:
		return "Test Two";
	case GAME_KIND::THREE_PLAYER:
		return "Three Player";
	case GAME_KIND::TEST_THREE:
		return "Test Three";
	case GAME_KIND::FOUR_PLAYER:
		return "Four Player";
	case GAME_KIND::TEST_FOUR:
		return "Test Four";
	case GAME_KIND::FINDINGJ:
		return "FindingJ";
	default:
		return "Unknown";
	}
}