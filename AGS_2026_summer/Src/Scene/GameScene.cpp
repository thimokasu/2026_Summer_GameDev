#include "GameScene.h"
#include<DxLib.h>

#include"../Manager/Game/SceneManager.h"
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Generic/KeyManager.h"

#include"../Manager/System/PhysicsSystem/PhysicsSystem.h"
#include"../Manager/System/CollisionSystem/CollisionSystem.h"
#include"../Manager/System/ContactSystem/ContactSystem.h"
#include"../Manager/System/ContactSystem/GameContactSystem.h"
#include"../Manager/System/MoveInputSystem/MoveInputSystem.h"

#include "../Net/NetManager.h"


GameScene::GameScene(void)
{
	gameInfo_.gameMode = GAMEKMODE::FourPlayer;
	gameInfo_.gameID = static_cast<Game>(FourPlayer::Game::FindingJ);
	gameInfo_.stageID = static_cast<int>(FourPlayer::FindingJ::Stage::Stage3);
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
			Entity entA{ a, actorManager_.GetKind(a) };
			Entity entB{ b, actorManager_.GetKind(b) };
			contactSystem_.OnBeginContact(entA, entB, CollisionResult{});
		};
	auto onEndContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorManager_.GetKind(a) };
			Entity entB{ b, actorManager_.GetKind(b) };
			contactSystem_.OnEndContact(entA, entB, CollisionResult{});
		};

	collisionSystem_.SetContactCallbacks(onBeginContact, onEndContact);

	actorManager_.Init();

	for (auto& actor : actorManager_.GetActors())
	{
	collisionSystem_.AddCollider(actor->GetOwnColliders());
	}

	stepCountDown_ = 3.0f;
}

void GameScene::Update(void)
{

	auto& nIns = NetManager::GetInstance();
	if (nIns.GetMode() == NET_MODE::HOST)
	{
		// ƒQ[ƒ€ŽžŠÔis
		SceneManager::GetInstance().ForwardGameTime();
	}

	float limit = stepCountDown_ - SceneManager::GetInstance().GetTotalGameTime();
	if (limit > 0.0f)
	{
		DrawFormatString(100, 100, 0xffffff, "%f", limit);
		return;
	}
	else
	{
		NetManager::GetInstance().ChangeGameState(GAME_STATE::GAME_PLAYING);
	}

	NetManager::GetInstance().ResetAction();

	actorManager_.Update();

	moveInputSystem_.Update(actorManager_.GetActors());
	physicsSystem_.Update(actorManager_.GetActors());

	collisionSystem_.Update();
	physicsSystem_.Resolve(actorManager_.GetActors(),collisionSystem_.GetCollisionMainfold());

	gameContactSystem_.Update(contactSystem_.GetContactEvent());
	contactSystem_.Clear();

	NetManager::GetInstance().Send(NET_DATA_TYPE::ACTION_HIS_ALL);

}

void GameScene::Draw(void)
{
	DrawString(0, 0, "game", 0xffffff);

	actorManager_.Draw();


}

void GameScene::Release(void)
{
	actorManager_.Release();


}
