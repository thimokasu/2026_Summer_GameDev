#include "ActorManager.h"
#include<DxLib.h>
#include"../../../Scene/GameSelect/GameKind.h"
#include"../Factory/ActorFactory/ActorFactoryBase.h"
#include"../Collider/ColliderBase.h"
#include"../Factory/ActorFactory/Test/TestFactory.h"
#include"../Factory/ActorFactory/FindingJ/Stage1Factory.h"
#include"../Factory/ActorFactory/FindingJ/Stage2Factory.h"
#include"../Factory/ActorFactory/FindingJ/Stage3Factory.h"

#include"../Charactor/Player/FindingJ/FindingJCPU/FindingJRunner.h"
#include"../../../Manager/Generic/KeyManager.h"

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
	actors_.push_back(std::make_unique<FindingJRunner>(*this));

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
					collider->Draw();
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
		break;
	case PLAY_NUM::TWO_PLAYER:

		break;
	case PLAY_NUM::THREE_PLAYER:

		break;
	case PLAY_NUM::FOUR_PLAYER:
		break;
	}
}
