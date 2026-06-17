#pragma once
#include<string>

enum class GAME_KIND
{
	NONE = -1,

	// 1人用
	ONE_PLAYER = 10,
	ATHLETIC,
	//2人用
	TWO_PLAYER = 20,
	THUMB_WRESTLING,
	SURVIVAL_TETRIS,
	//4人用
	ONE_VS_THERR = 30,

	TWO_VS_TWO=40,
	AIR_HOCKEY,


	FOUR_PLAYER = 50,
	FINDINGJ,
	TEST_OB_COURAGE,
	BUTTON_MASHING,
	KEY_CLIMBER,
};

enum class PLAY_NUM
{
	ONE_PLAYER,
	TWO_PLAYER,
	ONE_VS_THERR,
	TWO_VS_TWO,
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
	case GAME_KIND::THUMB_WRESTLING:
		return "ThumbWrestling";
	case GAME_KIND::SURVIVAL_TETRIS:
		return "SurvivalTetris";

	case GAME_KIND::ONE_VS_THERR:
		return "OneVsTherr";
	case GAME_KIND::AIR_HOCKEY:
		return "AirHockey";

	case GAME_KIND::TWO_VS_TWO:
		return "TwoVsTwo";

	case GAME_KIND::FOUR_PLAYER:
		return "Four Player";
	case GAME_KIND::TEST_FOUR:
		return "Test Four";
	case GAME_KIND::FINDINGJ:
		return "FindingJ";
	case GAME_KIND::TEST_OB_COURAGE:
		return "TestObCourage";
	case GAME_KIND::BUTTON_MASHING:
		return "ButtonMashing";
	case GAME_KIND::KEY_CLIMBER:
		return "KeyClimber";
	default:
		return "Unknown";
	}
}