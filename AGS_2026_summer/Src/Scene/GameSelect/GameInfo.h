#pragma once
#include<string>

enum class GAME_KIND
{
	NONE = -1,

	TEST,

	// 1人用
	ONE_PLAYER = 10,
	ATHLETIC,
	//2人用
	TWO_PLAYER = 20,
	THUMB_WRESTLING,
	SURVIVAL_TETRIS,
	//4人用
	//1VS3
	ONE_VS_THERR = 30,
	SPIKE_DROP,
	//2VS2
	TWO_VS_TWO=40,
	AIR_HOCKEY,

	FOUR_PLAYER = 50,
	FINDINGJ,
	TEST_OB_COURAGE,
	BUTTON_MASHING,
	KEY_CLIMBER,

	//1~4人用
	ONE_TO_FOUR_PLAYER = 60,
	FEEDJ,

	
	//全人数対応(できたら)
	UNICYCLE,

	MAX
};

enum class PLAY_NUM
{
	ONE_PLAYER,
	TWO_PLAYER,
	ONE_VS_THERR,
	TWO_VS_TWO,
	FOUR_PLAYER,
	ONETOFOURPLAYER,

	MAX
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
	case GAME_KIND::TEST:
		return "Test";

	case GAME_KIND::ONE_PLAYER:
		return "One Player";

	case GAME_KIND::TWO_PLAYER:
		return "Two Player";
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
	case GAME_KIND::FINDINGJ:
		return "FindingJ";
	case GAME_KIND::TEST_OB_COURAGE:
		return "TestObCourage";
	case GAME_KIND::BUTTON_MASHING:
		return "ButtonMashing";
	case GAME_KIND::KEY_CLIMBER:
		return "KeyClimber";
	case GAME_KIND::ONE_TO_FOUR_PLAYER:
		return"OneToFourPlayer";
	case GAME_KIND::FEEDJ:
		return "FeedJ";
	case GAME_KIND::UNICYCLE:
		return "Unicycle";
	case GAME_KIND::ATHLETIC:
		return "Athletic";
	case GAME_KIND::SPIKE_DROP:
		return "SpikeDrop";
	default:
		return "Unknown";
	}
}