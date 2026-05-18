#include "ActorManager.h"
#include<DxLib.h>
#include"../../../Scene/GameSelect/GameKind.h"
#include"../Factory/ActorFactory/ActorFactoryBase.h"
#include"../Collider/ColliderBase.h"
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
	for (auto& actor : actors_)
	{
		actor->Draw();
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
