#pragma once


enum class EntityKind
{
	//‹¤’Ê
	NONE = 0,
	CAMERA,
	STAGE,
	PLAYER,

	//MarbleRace
	MARBLE,
	MARBLE_GOAL,

	//FindingJ
	BLOCK,
	REACTION_BLOCK,
	FINDINGJ_CPU,

	//SpikeDrop
	SPIKE,

	//FeedJ
	STATION,
	FOOD,
	CONTAINER,
	STORAGE,
	TRASH,
	SERVE,

	//Athletic
	ATHLETIC_CLOUD,
	ATHLETIC_GOAL,
	ATHLETIC_FALL,

};