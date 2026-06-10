#pragma once

enum class GAME_KIND
{
	NONE = -1,

	// 1人用
	ONE_PLAYER=10,

	//2人用
	TWO_PLAYER=20,

	//3人用
	THREE_PLAYER=30,

	//4人用
	FOUR_PLAYER=40,

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
};


