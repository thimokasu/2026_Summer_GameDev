#include "GameScene.h"
#include<DxLib.h>
#include "../Application.h"

#include"../Manager/Game/SceneManager.h"
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Generic/KeyManager.h"

#include"../Manager/System/PhysicsSystem/PhysicsSystem.h"
#include"../Manager/System/CollisionSystem/CollisionSystem.h"
#include"../Manager/System/ContactSystem/ContactSystem.h"
#include"../Manager/System/ContactSystem/GameContactSystem.h"
#include"../Manager/System/MoveInputSystem/MoveInputSystem.h"

#include "../Object/Actor/Stage/FindingJ/ReactionBlock.h"
#include "../Object/UI/GameMessageUI.h"
#include <EffekseerForDXLib.h>

#include "../Object/Common/SE.h"





GameScene::GameScene(void)
{
	gameInfo_.gameMode = GAMEKMODE::TwoPlayer;
	gameInfo_.gameID = static_cast<Game>(TwoPlayer::Game::SwordFight);
	gameInfo_.stageID = static_cast<int>(TwoPlayer::SwordFight::Stage::Stage1);
	SE::GetInstance().Load(SOUND_TYPE::BGM, "Data/BGM/GameBGM.mp3");
}

GameScene::GameScene(GameInfo info)
{
	gameInfo_ = info;
}

GameScene::~GameScene(void)
{
}

template<typename T>
std::vector<std::shared_ptr<T>> ObjSearch(const std::vector<std::shared_ptr<ActorBase>>& objects)
{
	static_assert(std::is_base_of_v<ActorBase, T>);

	std::vector<std::shared_ptr<T>> out;
	out.reserve(objects.size());

	for (const auto& obj : objects)
	{
		if (!obj) continue;

		if (auto casted = std::dynamic_pointer_cast<T>(obj))
		{
			out.push_back(casted);
		}
	}
	return out;
}

void GameScene::Load(void)
{
	actorManager_.Load(gameInfo_);
}

void GameScene::Init(void)
{
	auto onBeginContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorManager_.GetKind(a), actorManager_.FindActor(a) };
			Entity entB{ b, actorManager_.GetKind(b), actorManager_.FindActor(b) };
			contactSystem_.OnBeginContact(entA, entB, CollisionResult{});
		};
	auto onEndContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorManager_.GetKind(a), actorManager_.FindActor(a) };
			Entity entB{ b, actorManager_.GetKind(b), actorManager_.FindActor(b) };
			contactSystem_.OnEndContact(entA, entB, CollisionResult{});
		};

	collisionSystem_.SetContactCallbacks(onBeginContact, onEndContact);

	auto onEventCollback = [this](uint32_t a)
		{
			std::dynamic_pointer_cast<ReactionBlock>(actorManager_.FindActor(a))->StepOn();
		};

	gameContactSystem_.SetEventCallback(onEventCollback);

	auto onCaughtCallback = [this]()
		{
			UI_.SetMessageState(GameMessageUI::MessageState::Finish);
		};

	gameContactSystem_.SetCaughtCallback(onCaughtCallback);

	actorManager_.Init();

	for (auto& actor : actorManager_.GetActors())
	{
	collisionSystem_.AddCollider(actor->GetOwnColliders());
	}

	UI_.Initialize();

	UI_.SetMessageState(GameMessageUI::MessageState::Explain);

	

}

void GameScene::Update(void)
{


	actorManager_.Update();



	if (UI_.GetState() == GameMessageUI::MessageState::None)
	{

		moveInputSystem_.Update(actorManager_.GetActors());
		physicsSystem_.Update(actorManager_.GetActors());
	}

	collisionSystem_.Update();
	physicsSystem_.Resolve(actorManager_.GetActors(), collisionSystem_.GetCollisionMainfold());

	gameContactSystem_.Update(contactSystem_.GetContactEvent());
	contactSystem_.Clear();

	UI_.Update();

	static bool isBGMPlayed = false;
	if (!isBGMPlayed && UI_.GetState() == GameMessageUI::MessageState::None)
	{
		SE::GetInstance().Play(SOUND_TYPE::BGM, true);
		isBGMPlayed = true;
	}


}

void GameScene::Draw(void)
{
	DrawString(0, 0, "game", 0xffffff);

	actorManager_.Draw();
	gameContactSystem_.DrawDebug();
	UI_.Draw();
	/*int handle_ = LoadEffekseerEffect("Data/Effect/Light/Light.efk");
	SetPosPlayingEffekseer3DEffect(handle_, 100, 100, 100);*/
}

void GameScene::Release(void)
{
	actorManager_.Release();
	SE::GetInstance().Stop(SOUND_TYPE::BGM);


}
