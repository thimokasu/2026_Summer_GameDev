#include "FindingJ.h"

#include"../../../../Manager/Game/SceneManager.h"

#include"../../../../Object/Actor/Manager/ActorManager.h"

#include"../../../../Object/Actor/Camera/Camera.h"

#include"../../../../Object/Actor/Charactor/FindingJ/FindingJCPU/FindingJRunner.h"
#include"../../../../Object/Actor/Charactor/FindingJ/FindingJCPU/FindingJChaser.h"
#include"../../../../Object/Actor/Charactor/FindingJ/FindingJPlayer.h"

#include"../../../../Object/UI/Common/GameMessageUI.h"
#include"../../../../Object/UI/Common/Timer.h"

FindingJ::FindingJ(ActorManager* actMng, CollisionManager* colMng)
	:GameBase(actMng,colMng)
{
}

FindingJ::~FindingJ(void)
{
}

void FindingJ::SubLoad(void)
{
	actorMng_->AddActor(std::make_unique<FindingJRunner>(*actorMng_));
}
void FindingJ::SubInit(void)
{
	auto cpu = actorMng_->FindActorsByKind(EntityKind::FINDINGJ_CPU);
	for (auto& c : cpu)
	{
		auto& findingJCPU = dynamic_cast<FindingJRunner&>(*c);
		findingJCPU.SetStageNum(gameInfo_.stage_);
	}	
	time = -4;
}
void FindingJ::SubUpdate(void)
{
	time += SceneManager::GetInstance().GetDeltaTime();
	if (time > 15)
	{
		time = 0;
		auto a = actorMng_->FindActorsByKind(EntityKind::FINDINGJ_CPU);
		for (auto& actor : a)
		{
			auto& runner = dynamic_cast<FindingJRunner&>(*actor);
			runner.Appear();
		}
	}
}
void FindingJ::SubDraw(void)
{
	DrawFormatString(0, 140, 0xffffff, "time:%2f", time);
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
			auto ui = UIManager::GetInstance().GetUI<Timer>(UINAME::TIMER);
			ui->SetUpdate(false);
			auto massage = UIManager::GetInstance().GetUI<GameMessageUI>(UINAME::MASSAGE);
			massage->SetMassageState(GameMessageUI::MASSAGE_STATE::FINISH);
		}
	);
}



void FindingJ::SetEventCallBack(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::START, [this](const ContactRule& rule)
		{
			OnUpdate();
			auto ui = UIManager::GetInstance().GetUI<Timer>(UINAME::TIMER);
			ui->SetUpdate(true);
		}
	);

	EventManager::GetInstance().SetContactEventCallback(GameEventType::TIME_UP, [this](const ContactRule& rule)
		{
			OffUpdate();
			auto massage = UIManager::GetInstance().GetUI<GameMessageUI>(UINAME::MASSAGE);
			massage->SetMassageState(GameMessageUI::MASSAGE_STATE::FINISH);
		}
	);
}

void FindingJ::LoadUI(void)
{
	auto msgUI = std::make_shared<GameMessageUI>(Vector2F(400.0f, 200.0f), Vector2F(400.0f, 100.0f));
	UIManager::GetInstance().AddRootUI(msgUI);
	msgUI->Load();
	msgUI->Init();
	msgUI->SetStartCallBack([this]()
		{
			EventManager::GetInstance().TriggerEvent(GameEventType::START);
		}
	);

	auto timerUI = std::make_shared<Timer>(Vector2F(50.0f, 50.0f), Vector2F(200.0f, 50.0f));
	UIManager::GetInstance().AddRootUI(timerUI);
	timerUI->Load();
	timerUI->Init();
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

	auto msgUI = UIManager::GetInstance().GetUI<GameMessageUI>(UINAME::MASSAGE);
	msgUI->SetMassageText(GameMessageUI::MASSAGE_STATE::EXPLAIN, "FIND J");
	msgUI->SetMassageText(GameMessageUI::MASSAGE_STATE::START, "START!");
	msgUI->SetMassageText(GameMessageUI::MASSAGE_STATE::FINISH, "FINISH!");

	auto timer = UIManager::GetInstance().GetUI<Timer>(UINAME::TIMER);
	timer->SetTime(60);
}

void FindingJ::InitSE(void)
{

}

void FindingJ::InitCamera(void)
{
	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(1.18f, 0.0f, 0.0f));
	SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(170.0f, 270.0f, 20.0f));
}


