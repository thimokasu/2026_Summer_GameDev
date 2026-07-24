#include "SpikeDrop.h"
#include"../../../../../Object/Actor/Item/SpikeDrop/Spike.h"
#include"../../../../../Object/Actor/Charactor/OneVsThree/SpikeDrop/Dropper.h"
#include"../../../../../Object/Actor/Manager/ActorManager.h"
#include"../../../../../Object/Actor/Charactor/OneVsThree/SpikeDrop/SpikeDropPlayer.h"
#include"../../../../../Object/Actor/Charactor/OneVsThree/SpikeDrop/State/SpikeDropPlayerHit.h"
#include"../../../../../Object/Actor/Camera/Camera.h"
#include"../../../../../Manager/Game/SceneManager.h"
#include"../../../../../Utility/AsoUtility.h"
#include "../../../../../Object/UI/FindingJ/GameMessageUI.h"

SpikeDrop::SpikeDrop(ActorManager* actMng, CollisionManager* colMng):GameBase(actMng,colMng)
{
}

SpikeDrop::~SpikeDrop(void)
{
}

void SpikeDrop::SubLoad(void)
{
}

void SpikeDrop::SubInit(void)
{
	isUpdate_ = true;

}

void SpikeDrop::SubUpdate(void)
{
	auto players = actorMng_->FindActorsByKind(EntityKind::PLAYER);

	// 例：全員がヒット状態になったかどうかを判定する場合
	bool allHit = true;
	static bool one = false;

	for (auto p : players)
	{
		SpikeDropPlayer* player = dynamic_cast<SpikeDropPlayer*>(p);
		if (player == nullptr) continue;

		// もし一人でもヒットしていなければ「続行」する
		if (!player->GetNowState<SpikeDropPlayerHit>())
		{
			allHit = false;
			continue; // 次のプレイヤーのチェックへ進む（ヒットしてなければここで処理を止めない）
		}
	}

	// 全員ヒットしていたら更新をストップする
	if (allHit && !players.empty()&&!one)
	{
		EventManager::GetInstance().TriggerEvent(GameEventType::FINISH);
		one = true;
	}
}

void SpikeDrop::SubDraw(void)
{
	//カメラ座標
	DrawFormatString(0, 0, 0xffffff, "Camera Position: %f, %f, %f",
		SceneManager::GetInstance().GetCamera().GetPos().x,
		SceneManager::GetInstance().GetCamera().GetPos().y,
		SceneManager::GetInstance().GetCamera().GetPos().z);
	DrawFormatString(0, 20, 0xffffff, "Camera Angles: %f, %f, %f",
		SceneManager::GetInstance().GetCamera().GetAngles().x,
		SceneManager::GetInstance().GetCamera().GetAngles().y,
		SceneManager::GetInstance().GetCamera().GetAngles().z);
}

void SpikeDrop::SubRelease(void)
{
}

void SpikeDrop::SetContactEventRule(void)
{
	EventManager::GetInstance().SetEventRule( EntityKind::PLAYER, EntityKind::SPIKE, GameEventType::SPIKE_HIT);
}

void SpikeDrop::SetContactEventCallback(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::SPIKE_HIT, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			SpikeDropPlayer* player = nullptr;
			Spike* spike = nullptr;
			if (entityKindA == EntityKind::PLAYER) { player = dynamic_cast<SpikeDropPlayer*>(actorA); spike = dynamic_cast<Spike*>(actorB); }
			if(entityKindB==EntityKind::PLAYER){player= dynamic_cast<SpikeDropPlayer*>(actorB); spike = dynamic_cast<Spike*>(actorA);}
			if (!player || !spike)return;
			player->GetTransform().pos = VGet(player->GetTransform().pos.x, player->GetTransform().pos.y, 100);
			player->GetRigidBody().AddForce(VGet(0, 20, -20));
			player->ChangeState<SpikeDropPlayerHit>();
			player->GetTransform().quaRot = Quaternion::Euler(VGet(0, 180, 0));
		});
}

void SpikeDrop::SetEventCallBack(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::CREATE_SPIKE, [this]()
		{
 			auto dropper = actorMng_->FindActorsByKind(EntityKind::DROPPER).back();
			auto dPos = dropper->GetTransform().pos;
			auto spike = std::make_unique<Spike>();
			spike->Load();
			spike->Init();
			spike->GetTransform().pos = dPos;
			spike->GetTransform().pos.y += -30;
			actorMng_->AddActor(std::move(spike), this);
		});
	EventManager::GetInstance().SetContactEventCallback(GameEventType::FINISH, [this]()
		{
			auto massage = UIManager::GetInstance().GetUI<GameMessageUI>(UINAME::MASSAGE);
			massage->SetMassageState(GameMessageUI::MASSAGE_STATE::FINISH); 
		});
}

void SpikeDrop::LoadUI(void)
{
	msgUI_ = std::make_shared<GameMessageUI>(Vector2F(Application::SCREEN_SIZE_X / 2
		, Application::SCREEN_SIZE_Y / 2), Vector2F(400.0f, 100.0f));
	msgUI_->Load();
	msgUI_->Init();

	UIManager::GetInstance().AddRootUI(msgUI_);
}

void SpikeDrop::LoadSE(void)
{
}

void SpikeDrop::InitUI(void)
{
	msgUI_->SetMassageText(GameMessageUI::MASSAGE_STATE::EXPLAIN, "AVOID SPIKE!");
	msgUI_->SetMassageText(GameMessageUI::MASSAGE_STATE::START, "START!");
	msgUI_->SetMassageText(GameMessageUI::MASSAGE_STATE::FINISH, "FINISH!");
}

void SpikeDrop::InitSE(void)
{
}

void SpikeDrop::InitCamera(void)
{
	SceneManager::GetInstance().GetCamera().ChangeMode(Camera::MODE::FREE);
	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(0,0 , 0.0f));
	SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(0, 100, -300));

}
