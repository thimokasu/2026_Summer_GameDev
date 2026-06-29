#include "ActorManager.h"
#include<DxLib.h>

#include"../Shape/Box.h"
#include"../Shape/Capsule.h"
#include"../Shape/Sphere.h"
#include"../Shape/ShapeBase.h"

#include"../Component/PlayerInputComponent/PlayerInputComponent.h"
#include"../Component/RigidBodyComponent/RigidBody.h"
#include "../Component/FindingJComponent/RunnerAIComponent/RunnerAIComponent.h"
#include "../Component/FindingJComponent/ChaserAIComponent/ChaserAIComponent.h"

#include"../ActorBase.h"
#include"../../Common/Transform.h"
#include"../Floor/Floor.h"
#include"../Camera/Camera.h"


#include"../../Actor/Factory/ActorFactory/ActorFactoryBase.h"
#include"../../Actor/Factory/ActorFactory/FindingJ/Stage1Factory.h"
#include"../../Actor/Factory/ActorFactory/FindingJ/Stage2Factory.h"
#include"../../Actor/Factory/ActorFactory/FindingJ/Stage3Factory.h"
#include "../../Actor/Factory/ActorFactory/SwordFight/Stage.h"

#include "../../Actor/Factory/ActorFactory/FindingJ/Player/Character.h"

#include "../../../Manager/Generic/KeyManager.h"

ActorManager::ActorManager()
{
	isShowCollider_ = false;
}

ActorManager::~ActorManager()
{
}



void ActorManager::Load(void)
{
}

void ActorManager::Load(GameInfo info)
{
	SetFactory(info);

	for (auto& actor : actorFactory_)
	{
		for (auto& create : actor->CreateActors())
		{
			actors_.push_back(create);
		}
	}
	
}

void ActorManager::Init(void)
{
	for (auto& actor : actors_)
	{
		actor->Init();
		actor->SetEntityId(entityId_++);	
		
	}
}

void ActorManager::Update(void)
{
	BindId2Kind();
	for (auto& actor : actors_)
	{
		actor->Update();
	}
}

void ActorManager::Draw(void)
{
	for (auto& actor : actors_)
	{
		actor->Draw();
		for (const auto& [shape, collider] : actor->GetOwnColliders() )
		{
			if (actor->GetEntityKind() != EntityKind::RUNNER)
			{
				collider->Draw();
			}
			else
			{
				if (KeyManager::GetIns().GetInfo(KEY_TYPE::ENTER).down)
				{
					isShowCollider_ = !isShowCollider_;
				}
				if (isShowCollider_)
				{
					collider->Draw();
				}
				
			}
		}

		if (actor->GetEntityKind() == EntityKind::PLAYER)
		{
			DrawFormatString(0, 20, 0xFFFFFF, "%f,%f,%f", actor->GetTransform().pos.x, actor->GetTransform().pos.y, actor->GetTransform().pos.z);
		}
	}
}

void ActorManager::Release(void)
{
	for (auto& actors_ : actors_)
	{
		actors_->Release();
	}
	actors_.clear();
}


EntityKind ActorManager::GetKind(int entityId_)
{
	return id2Kind_[entityId_];
}

void ActorManager::BindId2Kind(void)
{
	for (auto& obj : actors_)
	{
		id2Kind_[obj->GetEntityId()] = obj->GetEntityKind();
	}
}

void ActorManager::SetFactory(GameInfo info)
{
	switch (info.gameMode)
	{
	case GAMEKMODE::OnePlayer:
		switch (static_cast<OnePlayer::Game>(info.gameID))
		{
		case OnePlayer::Game::FindingJ:
			if (info.stageID == 0)
			{
				actorFactory_.push_back(std::make_unique<Stage3Factory>());
			}
			else if (info.stageID == 1)
			{
			}
			else if (info.stageID == 2)
			{
			}
			break;

		}
		break;
	case GAMEKMODE::TwoPlayer:
		switch (static_cast<TwoPlayer::Game>(info.gameID))
		{
		case TwoPlayer::Game::SwordFight:
			if (info.stageID == (int)TwoPlayer::SwordFight::Stage::Stage1)
			{
				actorFactory_.push_back(std::make_unique<Stage>());
				break;
			}
			break;
		case TwoPlayer::Game::B:
			if (info.stageID == 0)
			{
			}
			else if (info.stageID == 1)
			{
			}
			else if (info.stageID == 2)
			{
			}
			break;
		}
		break;
	case GAMEKMODE::ThreePlayer:
		switch (static_cast<ThreePlayer::Game>(info.gameID))
		{
		case ThreePlayer::Game::A:
			if (info.stageID == 0)
			{
			}
			else if (info.stageID == 1)
			{
			}
			else if (info.stageID == 2)
			{
			}
			break;
		case ThreePlayer::Game::B:
			if (info.stageID == 0)
			{
			}
			else if (info.stageID == 1)
			{
			}
			else if (info.stageID == 2)
			{
			}
			break;
		}
		break;
	case GAMEKMODE::FourPlayer:
		switch (static_cast<FourPlayer::Game>(info.gameID))
		{
		case FourPlayer::Game::FindingJ:
			if (info.stageID == 0)
			{
				actorFactory_.push_back(std::make_unique<Stage1Factory>());
				break;
			}
			else if (info.stageID == 1)
			{
				actorFactory_.push_back(std::make_unique<Stage2Factory>());
				break;
			}
			else if (info.stageID == 2)
			{
				actorFactory_.push_back(std::make_unique<Stage3Factory>());
				break;
			}
			break;
		case FourPlayer::Game::B:
			if (info.stageID == 0)
			{
			}
			else if (info.stageID == 1)
			{
			}
			else if (info.stageID == 2)
			{
			}
			break;
		}
		break;
	}

	actorFactory_.push_back(std::make_unique<Character>(info));

}

