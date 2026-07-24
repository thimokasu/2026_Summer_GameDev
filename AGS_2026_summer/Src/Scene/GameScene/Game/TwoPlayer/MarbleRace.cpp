#include "MarbleRace.h"
#include"../../../../Manager/Game/SceneManager.h"

#include"../../../../Object/Actor/Manager/ActorManager.h"

#include"../../../../Object/Actor/Camera/Camera.h"

#include"../../../../Object/UI/FindingJ/GameMessageUI.h"

#include"../../../../Object/Actor/Charactor/TwoPlay/MarbleRace/MarbleRacePlayer.h"
#include"../../../../Object/Actor/Charactor/TwoPlay/MarbleRace/State/MarbleRaveAttack.h"
#include"../../../../Object/Actor/Charactor/TwoPlay/MarbleRace/State/MarbleRaceHit.h"
#include"../../../../Object/Actor/Stage/MarbleRace/MarbleRaceGoal.h"


MarbleRace::MarbleRace(ActorManager* actMng, CollisionManager* colMng) :GameBase(actMng, colMng)
{
}

MarbleRace::~MarbleRace(void)
{
}

void MarbleRace::SubLoad(void)
{
}

void MarbleRace::SubInit(void)
{
	SetLightDirection(VGet(0.6f, -3.14f, 0.0f));
}

void MarbleRace::SubUpdate(void)
{
	SceneManager::GetInstance().GetCamera().StopMove();
	static int start = 0;
	start++;
	if (start > 500) {
		isUpdate_ = true;
		start = 0;
	}
	if (!isUpdate_)return;
	auto pos = SceneManager::GetInstance().GetCamera().GetTransform().pos;
	if (pos.z >= 500)
	{

	}
	else
	{
	SceneManager::GetInstance().GetCamera().SetCameraPos(VAdd(pos, VGet(0, 0, 0.3f)));
	}
}

void MarbleRace::SubDraw(void)
{
	//ƒJƒƒ‰À•W
DrawFormatString(0,0,0xffffff,"Camera Position: %f, %f, %f",
	SceneManager::GetInstance().GetCamera().GetPos().x,
	SceneManager::GetInstance().GetCamera().GetPos().y,
	SceneManager::GetInstance().GetCamera().GetPos().z);
DrawFormatString(0, 20, 0xffffff, "Camera Angles: %f, %f, %f",
	SceneManager::GetInstance().GetCamera().GetAngles().x,
	SceneManager::GetInstance().GetCamera().GetAngles().y,
	SceneManager::GetInstance().GetCamera().GetAngles().z);
}

void MarbleRace::SubRelease(void)
{
}

void MarbleRace::SetContactEventRule(void)
{
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::PLAYER, GameEventType::PLAYER_HIT);
	EventManager::GetInstance().SetEventRule(EntityKind::PLAYER, EntityKind::MARBLE_GOAL, GameEventType::MARBLE_RACE_GOAL);
}

void MarbleRace::SetContactEventCallback(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::PLAYER_HIT, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			MarbleRacePlayer* player1;
			MarbleRacePlayer* player2;
			player1 = dynamic_cast<MarbleRacePlayer*>(actorA);
			player2 = dynamic_cast<MarbleRacePlayer*>(actorB);
			if (!player1 || !player2)return;
			if (player1->GetNowState<MarbleRaceAttack>()!=nullptr)
			{
				player2->ChangeState<MarbleRaceHit>();
			}
			else if (player2->GetNowState<MarbleRaceAttack>()!=nullptr)
			{
				player1->ChangeState<MarbleRaceHit>();
			}
		});

	EventManager::GetInstance().SetContactEventCallback(GameEventType::MARBLE_RACE_GOAL, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			MarbleRacePlayer* player=nullptr;
			MarbleRaceGoal* goal=nullptr;
			if (entityKindA == EntityKind::PLAYER) { player = dynamic_cast<MarbleRacePlayer*>(actorA); goal = dynamic_cast<MarbleRaceGoal*>(actorB); }
			if (entityKindB == EntityKind::PLAYER) { player = dynamic_cast<MarbleRacePlayer*>(actorB); goal = dynamic_cast<MarbleRaceGoal*>(actorA); }
			if (!player || !goal)return;
			auto p = dynamic_cast<MarbleRacePlayer*>(player);
			p->GetTransform().pos.z += 20;
			isUpdate_ = false;
			auto massage = UIManager::GetInstance().GetUI<GameMessageUI>(UINAME::MASSAGE);
			massage->SetMassageState(GameMessageUI::MASSAGE_STATE::FINISH);});
}

void MarbleRace::SetEventCallBack(void)
{
}

void MarbleRace::LoadUI(void)
{
	msgUI_ = std::make_shared<GameMessageUI>(Vector2F(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2), Vector2F(400, 100));
	msgUI_->Load();
	msgUI_->Init();
	UIManager::GetInstance().AddRootUI(msgUI_);
}

void MarbleRace::LoadSE(void)
{
}

void MarbleRace::InitUI(void)
{
	msgUI_->SetMassageText(GameMessageUI::MASSAGE_STATE::EXPLAIN, "GO FOR GOAL!");
	msgUI_->SetMassageText(GameMessageUI::MASSAGE_STATE::START, "START!");
	msgUI_->SetMassageText(GameMessageUI::MASSAGE_STATE::FINISH, "GOAL!");

}

void MarbleRace::InitSE(void)
{
}

void MarbleRace::InitCamera(void)
{
	SceneManager::GetInstance().GetCamera().ChangeMode(Camera::MODE::FIXED_POINT);
	SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(0, 100, -60));
	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(0.6f, 3.14f, 0.0f));
	SceneManager::GetInstance().GetCamera().StopMove();
}
