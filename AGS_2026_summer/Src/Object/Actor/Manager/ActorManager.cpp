#include "ActorManager.h"
#include<DxLib.h>
#include"../../../Scene/GameSelect/GameKind.h"
#include"../Factory/ActorFactory/ActorFactoryBase.h"
#include"../Collider/ColliderBase.h"
#include"../Factory/ActorFactory/Test/TestFactory.h"

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
		actor->Draw();

		// --- ここから追加：左上に座標をリスト表示 ---
		auto pos = actor->GetTransform().pos;

		// actorに名前やIDを取得する関数（GetName()など）があれば、"Player" などの代わりに使えます
		DrawFormatString(startX, startY + (index * lineHeight), GetColor(255, 255, 255),
			"Actor[%d] - X: %.1f, Y: %.1f", index, pos.x, pos.y);

		index++; // 次のアクターは1行下に下げる
		// ------------------------------------------

		for (const auto& [shape, collider] : actor->GetOwnColliders())
		{
			collider->Draw();
		}
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

void ActorManager::BindID2Kind(void)
{
	for (auto& obj : actors_)
	{
		id2kind_.emplace(obj->GetEntityID(), obj->GetEntityKind());
	}
}

void ActorManager::SetFactory(GameInfo info)
{
	switch (info.mode_)
	{
	case GameMode::TEST:
		switch (static_cast<Test::Game>(info.game_))
		{
		case Test::Game::A:
			if (info.stageNum_ == (int)Test::A::Stage::Stage1)
			{
				actorFactory_ = std::make_unique<TestFactory>();
			}
			break;
		}
		break;
	case GameMode::ONEPLAYER:
		switch (static_cast<OnePlayer::Game>(info.game_))
		{
		case OnePlayer::Game::A:
			if (info.stageNum_ == 0){
				
			}
			else if (info.stageNum_ == 1){
			}
			else {
			}
			break;
		case OnePlayer::Game::B:
			if (info.stageNum_ == 0) {
			}
			else if (info.stageNum_ == 1) {
			}
			else {
			}
			break;
		}
		break;
	case GameMode::TWOPLAYER:
		switch (static_cast<OnePlayer::Game>(info.game_))
		{
		case OnePlayer::Game::A:
			if (info.stageNum_ == 0) {
			}
			else if (info.stageNum_ == 1) {
			}
			else {
			}
			break;
		case OnePlayer::Game::B:
			if (info.stageNum_ == 0) {
			}
			else if (info.stageNum_ == 1) {
			}
			else {
			}
			break;
		}
		break;
	case GameMode::THREEPLAYER:
		switch (static_cast<OnePlayer::Game>(info.game_))
		{
		case OnePlayer::Game::A:
			if (info.stageNum_ == 0) {
			}
			else if (info.stageNum_ == 1) {
			}
			else {
			}
			break;
		case OnePlayer::Game::B:
			if (info.stageNum_ == 0) {
			}
			else if (info.stageNum_ == 1) {
			}
			else {
			}
			break;
		}
		break;
	case GameMode::FOURPLAYER:
		switch (static_cast<OnePlayer::Game>(info.game_))
		{
		case OnePlayer::Game::A:
			if (info.stageNum_ == 0) {
			}
			else if (info.stageNum_ == 1) {
			}
			else {
			}
			break;
		case OnePlayer::Game::B:
			if (info.stageNum_ == 0) {
			}
			else if (info.stageNum_ == 1) {
			}
			else {
			}
			break;
		}
		break;
	}
}
