#include "ActorManager.h"
#include<DxLib.h>
#include"../../../Scene/GameSelect/GameInfo.h"
#include"../Factory/ActorFactoryBase.h"
#include"../Collider/ColliderBase.h"
#include"../Factory/Test/TestFactory.h"
#include"../Factory/FactorysHeadersh.h"
#include"../Factory/FindingJ/Stage1Factory.h"
#include"../Factory/FindingJ/Stage2Factory.h"
#include"../Factory/FindingJ/Stage3Factory.h"
#include "../Factory/Unicycle/UnicycleFactory.h"
#include"../Factory/Athletic/AthleticFactory.h"

#include"../Charactor/FindingJ/FindingJCPU/FindingJRunner.h"
#include"../../../Manager/Generic/KeyManager.h"
#include"../../../Scene/GameScene/Game/GameBase.h"


ActorManager::ActorManager(void)
{
}

ActorManager::~ActorManager(void)
{
}


void ActorManager::Load(GameInfo info)
{
	SetFactory(info);
	for (auto& actor : actorFactory_->CreateActors())
	{
		actors_.push_back(std::move(actor));
	}

	for(auto&a:actors_)
	{
		a->Load();
	}
}

void ActorManager::Init(void)
{
	for(auto&actor:actors_)
	{
		actor->Init();
		actor->SetEntityID(entityID_++);
	}
}

void ActorManager::Update(void)
{
	BindID2Kind();
	for (auto& actor : actors_)
	{
		actor->Update();
	}
}

void ActorManager::Draw(void)
{
	// 左上の開始位置
	int startX = 20;
	int startY = 20;
	int lineHeight = 20; // 1行あたりの高さ（文字のサイズに合わせて調整）
	int index = 0;

	for (auto& actor : actors_)
	{
		if (actor->IsDraw())
		{
			actor->Draw();
			if (actor->GetTransform().modelId == -1)
			{

				for (const auto& [shape, collider] : actor->GetOwnColliders())
				{
					if (collider->GetColliderInfo().isDraw_)
					{
					collider->Draw();
					}
				}
			}
		}

		if (KEY::GetIns().GetInfo(KEY::KEY_TYPE::DEBUG).now)
		{
		}
		//// --- ここから追加：左上に座標をリスト表示 ---
		//auto pos = actor->GetTransform().pos;

		//// actorに名前やIDを取得する関数（GetName()など）があれば、"Player" などの代わりに使えます
		//DrawFormatString(startX, startY + (index * lineHeight), GetColor(255, 255, 255),
		//	"Actor[%d] - X: %.1f, Y: %.1f", index, pos.x, pos.y);

		//index++; // 次のアクターは1行下に下げる
		//// ------------------------------------------

	}
}

void ActorManager::Release(void)
{
	for (auto& actor : actors_)
	{
		actor->Release();
	}
	actors_.clear();
}


EntityKind ActorManager::GetEntityKind(EntityID id) const
{
	return id2kind_.at(id);
}

std::vector<ActorBase*> ActorManager::FindActorsByKind(EntityKind kind) const
{
	std::vector<ActorBase*>actors;

	for (const auto& a : actors_)
	{
		if (a->GetEntityKind() == kind)
		{
			actors.push_back(a.get());
		}
	}
	return actors;
}

ActorBase* ActorManager::FindActorByID(EntityID id) const
{
for(const auto&a:actors_)
	{
		if (a->GetEntityID() == id)
		{
			return a.get();
		}
	}
	return nullptr;
}

void ActorManager::AddActor(std::unique_ptr<ActorBase> actor)
{
	actor->SetEntityID(entityID_++);
	actors_.push_back(std::move(actor));
}
void ActorManager::AddActor(std::unique_ptr<ActorBase> actor, GameBase* game)
{
	actor->SetEntityID(entityID_++);
	game->AddCollider(actor.get());
	actors_.push_back(std::move(actor));
}
void ActorManager::BindID2Kind(void)
{
	for (auto& obj : actors_)
	{
		id2kind_.emplace(obj->GetEntityID(), obj->GetEntityKind());
	}
}

void ActorManager::SetFactory(GameInfo info)
{
	switch (info.playNum_)
	{
	case PLAY_NUM::ONE_PLAYER:
		OnePlayerGameFactory(info);
		break;
	case PLAY_NUM::TWO_PLAYER:
		TwoPlayerGameFactory(info);
		break;

	case PLAY_NUM::FOUR_PLAYER:
		FourPlayerGameFactory(info);
		break;
	case PLAY_NUM::ONETOFOURPLAYER:
		OneToFourPlayerGameFactory(info);
		break;
	}
}

void ActorManager::OnePlayerGameFactory(GameInfo info)
{
	switch (info.game_)
	{
	case GAME_KIND::TEST:
		actorFactory_ = std::make_unique<TestFactory>();
		break;
	case GAME_KIND::UNICYCLE:
		actorFactory_ = std::make_unique<UnicycleFactory>();
		break;
	case GAME_KIND::FINDINGJ:
		actorFactory_ = std::make_unique<Stage1Factory>();
			break;
	default:
		break;
	}
}

void ActorManager::TwoPlayerGameFactory(GameInfo info)
{
}

void ActorManager::ThreePlayerGameFactory(GameInfo info)
{
}

void ActorManager::FourPlayerGameFactory(GameInfo info)
{
	switch (info.game_)
	{
	case GAME_KIND::FINDINGJ:
		switch (info.stage_)
		{
		case STAGE_NUM::STAGE1:
			actorFactory_ = std::make_unique<Stage1Factory>();
			break;
		case STAGE_NUM::STAGE2:
			actorFactory_ = std::make_unique<Stage2Factory>();
			break;
		case STAGE_NUM::STAGE3:
			actorFactory_ = std::make_unique<Stage3Factory>();
			break;
		default:
			break;
		}
		break;
	case GAME_KIND::ATHLETIC:
		actorFactory_ = std::make_unique<AthleticFactory>();
		break;
	default:
		break;
	}
}

void ActorManager::OneToFourPlayerGameFactory(GameInfo info)
{
	switch (info.game_)
	{
	case GAME_KIND::FEEDJ:
		switch (info.stage_)
		{
		case STAGE_NUM::STAGE1:
			actorFactory_ = std::make_unique<FeedJStage1Factory>();
			break;
		case STAGE_NUM::STAGE2:
			break;
		case STAGE_NUM::STAGE3:
			break;
		default:
			break;
		}
	case GAME_KIND::UNICYCLE:
		actorFactory_ = std::make_unique<UnicycleFactory>();
		break;
	default:
		break;
	}
}
