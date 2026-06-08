#pragma once

struct GameInfo
{
	GAME_KIND game_;
	STAGE_NUM stage_;
	PLAY_NUM playNum_;
};


enum class GAME_KIND
{
	// 1人用

	//2人用

	//3人用

	//4人用
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
};