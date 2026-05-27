#include "GameScene.h"
#include<DxLib.h>
#include "../Application.h"

#include"../Manager/Game/SceneManager.h"
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Generic/KeyManager.h"

#include"../Manager/System/Collision/CollisionManager.h"
#include"../Manager/System/ContactSystem/ContactEventManager.h"

#include"../Object/Actor/Manager/ActorManager.h"

#include"../Object/Actor/Camera/Camera.h"
#include"../Object/Actor/Stage/FindingJ/ReactionBlock.h"

#include "../Object/UI/GameMessageUI.h"
#include <EffekseerForDXLib.h>


GameScene::GameScene(void)
{
	gameInfo_.mode_ = GameMode::FOURPLAYER;
	gameInfo_.game_ = static_cast<Game>(FourPlayer::Game::FindingJ);
	gameInfo_.stageNum_ = static_cast<int>(FourPlayer::FindingJ::Stage::Stage3);
}

GameScene::GameScene(GameInfo info)
{
	gameInfo_ = info;
}

GameScene::~GameScene(void)
{
}

void GameScene::Load(void)
{
	actorMng_ = std::make_unique<ActorManager>();
	colMng_ = std::make_unique<CollisionManager>();
	contactMng_ = std::make_unique<ContactEventManager>();
	actorMng_->Load(gameInfo_);
}

void GameScene::Init(void)
{
	auto onBeginContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorMng_->GetEntityKind(a) };
			Entity entB{ b, actorMng_->GetEntityKind(b) };
			contactMng_->OnBeginContact(entA, entB, CollisionResult{});
		};
	auto onEndContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorMng_->GetEntityKind(a) };
			Entity entB{ b, actorMng_->GetEntityKind(b) };
			contactMng_->OnEndContact(entA, entB, CollisionResult{});
		};
	colMng_->SetContactCallbacks(onBeginContact, onEndContact);	
	SetContactEventRule();
	SetContactEventCallback();

	actorMng_->Init();
	for (auto& actor : actorMng_->GetActors())
	{
		for (const auto& [shape, collider] : actor->GetOwnColliders())
		{
			colMng_->AddCollider(collider.get(), actor->GetEntityID());
		}
	}
	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(1.18f, 0.0f, 0.0f));
	SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(170.0f, 270.0f, 20.0f));

	UI_.Initialize();
}

void GameScene::Update(void)
{
	////エスケープ押したらメニューシーンへ
	//if (KeyManager::GetIns().GetInfo(KEY_TYPE::PAUSE).down)
	//{
	//	isPause_ = !isPause_;
	//}

	//if (isPause_)
	//{
	//	if (pauseScene_)
	//	{
	//		pauseScene_->Update();
	//	}
	//	return;
	//}

	//スペース押したらゲームシーンへ
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::SPACE).down)
	{
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		return;
	}


	actorMng_->Update();
	colMng_->Update();
	colMng_->Resolve();
	contactMng_->Update();

	UI_.Update();
}

void GameScene::Draw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Game");
	actorMng_->Draw();

	//if (isPause_)
	//{
	//	pauseScene_->Draw();
	//	return;
	//}

	UI_.Draw();
}

void GameScene::Release(void)
{
	actorMng_->Release();
	colMng_->ClearColliders();
}

void GameScene::SetContactEventRule(void)
{
	//イベントの発生ルールの設定
	contactMng_->SetEventRule(EntityKind::PLAYER, EntityKind::REACTION_BLOCK, GameEventType::REACTION_BLOCK);
	contactMng_->SetEventRule(EntityKind::PLAYER, EntityKind::FINDINGJ_CPU, GameEventType::HAS_CAHGHT);
}
void GameScene::SetContactEventCallback(void)
{
	//イベントのコールバック関数の設定
	contactMng_->SetContactEventCallback(GameEventType::REACTION_BLOCK, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			if (entityKindA == EntityKind::REACTION_BLOCK)
			{
				auto idA = rule.contactEvent_.entityA.entityID_;
				auto actor = actorMng_->FindActorByID(idA);
				auto& reactionBlock = dynamic_cast<ReactionBlock&>(*actor);
				reactionBlock.StepOn();
			}
			else if (entityKindB == EntityKind::REACTION_BLOCK)
			{
				auto idB = rule.contactEvent_.entityB.entityID_;
				auto actor = actorMng_->FindActorByID(idB);
				auto& reactionBlock = dynamic_cast<ReactionBlock&>(*actor);
				reactionBlock.StepOn();
			}
		}
	);
	contactMng_->SetContactEventCallback(
		GameEventType::HAS_CAHGHT,
		[this]() { UI_.SetMessageState(
			GameMessageUI::MessageState::Finish); 
		}
	);

}
