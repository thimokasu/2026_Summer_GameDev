#pragma once
#include<cstdint>
#include<memory>
#include"GameEventType.h"
#include"../../../Object/Actor/ActorBase.h"
#include"../../../Object/Actor/EntityKind.h"
using EntityID = std::uint32_t;

struct Entity
{
	EntityID entityId;
	EntityKind entityKind;
	std::shared_ptr<ActorBase> actorPtr;
};


struct ContactEventInfo
{
	enum class Type
	{
		BEGIN,
		END,
	};

	Type type_;
	Entity entityA;
	Entity entityB;
};

struct ContactRule
{
	ContactEventInfo contactEvent_;
	GameEventType eventType_;
};



