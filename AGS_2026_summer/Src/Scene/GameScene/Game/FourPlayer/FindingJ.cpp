#include "FindingJ.h"

#include"../../../../Manager/Game/SceneManager.h"

#include"../../../../Object/Actor/Manager/ActorManager.h"

#include"../../../../Object/Actor/Camera/Camera.h"

#include"../../../../Object/Actor/Charactor/FindingJ/FindingJCPU/FindingJRunner.h"
#include"../../../../Object/Actor/Charactor/FindingJ/FindingJCPU/FindingJChaser.h"
#include"../../../../Object/Actor/Charactor/FindingJ/FindingJPlayer.h"

#include"../../../../Object/UI/FindingJ/GameMessageUI.h"
#include"../../../../Object/UI/FindingJ/Timer.h"

FindingJ::FindingJ(ActorManager* actMng, CollisionManager* colMng)
	:GameBase(actMng,colMng)
{
}

FindingJ::~FindingJ(void)
{
}

void FindingJ::SubLoad(void)
{

}
void FindingJ::SubInit(void)
{
	auto cpu = actorMng_->FindActorsByKind(EntityKind::FINDINGJ_CPU);
	for (auto& c : cpu)
	{
		auto& findingJCPU = dynamic_cast<FindingJRunner&>(*c);
		findingJCPU.SetStageNum(gameInfo_.stage_);
	}
}
void FindingJ::SubUpdate(void)
{
}
void FindingJ::SubDraw(void)
{
}
void FindingJ::SubRelease(void)
{
}

void FindingJ::SetContactEventRule(void)
{	
	//イベントの発生ルールの設定
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::REACTION_BLOCK, GameEventType::REACTION_BLOCK);
	EventManager::GetInstance().SetEventRule(EntityKind::FINDINGJ_CPU, EntityKind::REACTION_BLOCK, GameEventType::REACTION_BLOCK);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::FINDINGJ_CPU, GameEventType::HAS_CAHGHT);
}
void FindingJ::SetContactEventCallback(void)
{
	//イベントのコールバック関数の設定
	EventManager::GetInstance().SetContactEventCallback(GameEventType::REACTION_BLOCK, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			if (entityKindA == EntityKind::FINDINGJ_CPU)
			{
				auto idA = rule.contactEvent_.entityA.entityID_;
				auto actor = actorMng_->FindActorByID(idA);
				auto& findingJCPU = dynamic_cast<FindingJRunner&>(*actor);
				findingJCPU.Appear();
			}
			else if (entityKindB == EntityKind::FINDINGJ_CPU)
			{
				auto idB = rule.contactEvent_.entityB.entityID_;
				auto actor = actorMng_->FindActorByID(idB);
				auto& findingJCPU = dynamic_cast<FindingJRunner&>(*actor);
				findingJCPU.Appear();
			}
		}
	);
	EventManager::GetInstance().SetContactEventCallback(GameEventType::HAS_CAHGHT, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			if (entityKindA == EntityKind::FINDINGJ_CPU)
			{
				auto idA = rule.contactEvent_.entityA.entityID_;
				auto actor = actorMng_->FindActorByID(idA);
				auto& findingJCPU = dynamic_cast<FindingJRunner&>(*actor);
				findingJCPU.SetIsDraw(true);
				OffUpdate();
			}
			else if (entityKindB == EntityKind::FINDINGJ_CPU)
			{
				auto idB = rule.contactEvent_.entityB.entityID_;
				auto actor = actorMng_->FindActorByID(idB);
				auto& findingJCPU = dynamic_cast<FindingJRunner&>(*actor);
				findingJCPU.SetIsDraw(true);
				OffUpdate();
			}
			auto ui = UIManager::GetInstance().GetUI<Timer>(UINAME::FINDINGJ_TIMER);
			ui->SetUpdate(false);
			auto massage = UIManager::GetInstance().GetUI<GameMessageUI>(UINAME::FINDINGJ_MASSAGE);
			massage->SetMassageState(GameMessageUI::MASSAGE_STATE::FINISH);
		}
	);
}

void FindingJ::SetCollisionCollback(void)
{
	auto onBeginContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorMng_->GetEntityKind(a) };
			Entity entB{ b, actorMng_->GetEntityKind(b) };
			EventManager::GetInstance().OnBeginContact(entA, entB, CollisionResult{});
		};
	auto onEndContact = [this](uint32_t a, uint32_t b)
		{
			Entity entA{ a, actorMng_->GetEntityKind(a) };
			Entity entB{ b, actorMng_->GetEntityKind(b) };
			EventManager::GetInstance().OnEndContact(entA, entB, CollisionResult{});
		};
	colMng_->SetContactCallbacks(onBeginContact, onEndContact);
}

void FindingJ::SetEventCallBack(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::START, [this](const ContactRule& rule)
		{
			OnUpdate();
			auto ui = UIManager::GetInstance().GetUI<Timer>(UINAME::FINDINGJ_TIMER);
			ui->SetUpdate(true);
		}
	);

	EventManager::GetInstance().SetContactEventCallback(GameEventType::TIME_UP, [this](const ContactRule& rule)
		{
			OffUpdate();
			auto massage = UIManager::GetInstance().GetUI<GameMessageUI>(UINAME::FINDINGJ_MASSAGE);
			massage->SetMassageState(GameMessageUI::MASSAGE_STATE::FINISH);
		}
	);
}

void FindingJ::LoadUI(void)
{
	auto msgUI = std::make_shared<GameMessageUI>(Vector2F(400.0f, 200.0f), Vector2F(400.0f, 100.0f));
	UIManager::GetInstance().AddRootUI(msgUI);
	msgUI->Load();
	msgUI->SetStartCallBack([this]()
		{
			EventManager::GetInstance().TriggerEvent(GameEventType::START);
		}
	);

	auto timerUI = std::make_shared<Timer>(Vector2F(50.0f, 50.0f), Vector2F(200.0f, 50.0f));
	UIManager::GetInstance().AddRootUI(timerUI);
	timerUI->Load();
	timerUI->SetTimeUpCallBack([this]()
		{
			EventManager::GetInstance().TriggerEvent(GameEventType::TIME_UP);
		}
	);

}

void FindingJ::LoadSE(void)
{
	SE::GetInstance().Load(SOUND_TYPE::BGM, "Data/BGM/GameBGM.mp3");
}

void FindingJ::InitUI(void)
{

}

void FindingJ::InitSE(void)
{

}

void FindingJ::InitCamera(void)
{
	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(1.18f, 0.0f, 0.0f));
	SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(170.0f, 270.0f, 20.0f));
}


