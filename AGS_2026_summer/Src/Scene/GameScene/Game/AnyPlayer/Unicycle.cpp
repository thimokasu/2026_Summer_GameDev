#include "Unicycle.h"

#include"../../../../Manager/Game/SceneManager.h"

#include"../../../../Object/Actor/Manager/ActorManager.h"

#include"../../../../Object/Actor/Camera/Camera.h"

#include "../../../../Object/Actor/Charactor/OnePlay/Unicycle/UnicyclePlayer.h"

#include "../../../../Object/UI/FindingJ/GameMessageUI.h"
#include "../../../../Object/UI/Unicycle/Distance.h"
#include "../../../../Object/UI/Unicycle/CountTimer.h"
#include "../../../../Object/UI/Unicycle/MessageImageUI.h"

#include "../../../../Application.h"

Unicycle::Unicycle(ActorManager* actMng, CollisionManager* colMng)
	:GameBase(actMng, colMng)
{
}

Unicycle::~Unicycle(void)
{
}

void Unicycle::SubLoad(void)
{
}

void Unicycle::SubInit(void)
{
}

void Unicycle::SubUpdate(void)
{
}

void Unicycle::SubDraw(void)
{
	////カメラ座標
	//DrawFormatString(0,0,0xffffff,"Camera Position: %f, %f, %f",
	//	SceneManager::GetInstance().GetCamera().GetPos().x,
	//	SceneManager::GetInstance().GetCamera().GetPos().y,
	//	SceneManager::GetInstance().GetCamera().GetPos().z);
	//DrawFormatString(0, 20, 0xffffff, "Camera Angles: %f, %f, %f",
	//	SceneManager::GetInstance().GetCamera().GetAngles().x,
	//	SceneManager::GetInstance().GetCamera().GetAngles().y,
	//	SceneManager::GetInstance().GetCamera().GetAngles().z);
}

void Unicycle::SubRelease(void)
{
}

void Unicycle::SetContactEventRule(void)
{
}

void Unicycle::SetContactEventCallback(void)
{
}

void Unicycle::SetEventCallBack(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::START, [this](const ContactRule& rule)
		{
			OnUpdate();
		});

	//プレイヤーが落下したときのイベント
	auto player = actorMng_->FindActorsByKind(EntityKind::PLAYER);
	for (auto& p : player)
	{
		auto& player = dynamic_cast<UnicyclePlayer&>(*p);
		player.SetFallCallBack([this, &player]()
			{
				OffUpdate();
				//プレイヤーを画面外に飛ばす
				player.FallAfterGameEnd();
				//メッセージUIの表示
				auto massage = UIManager::GetInstance().GetUI<GameMessageUI>(UINAME::MASSAGE);
				massage->SetMassageState(GameMessageUI::MASSAGE_STATE::FINISH);
				VECTOR pos = SceneManager::GetInstance().GetCamera().GetPos();
				//固定カメラに切り替え
				SceneManager::GetInstance().GetCamera().ChangeMode(Camera::MODE::FREE);
				SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(0.73f, 0.0f, 0.0f));
				SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(pos.x, pos.y,pos.z));
			}
		);
	}

	//ゴール時のイベント
	distanceUI_->SetGoalCallBack([this]()
		{
			OffUpdate();
			ImageUI_->SetActive(true);
			VECTOR pos = SceneManager::GetInstance().GetCamera().GetPos();
			//固定カメラに切り替え
			SceneManager::GetInstance().GetCamera().ChangeMode(Camera::MODE::FREE);
			SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(0.73f, 0.0f, 0.0f));
			SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(pos.x, pos.y, pos.z));
		}
	);
}

void Unicycle::LoadUI(void)
{
	//距離UIの生成
	distanceUI_ = std::make_shared<Distance>(
		Vector2F(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y));
	UIManager::GetInstance().AddRootUI(distanceUI_);

	//画像UI
	ImageUI_ = std::make_shared<MessageImageUI>(
		Vector2F(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2));
	ImageUI_->Load();
	UIManager::GetInstance().AddRootUI(ImageUI_);

	//開始カウントUI
	auto countUI = std::make_shared<CountTimer>(
		Vector2F(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2));

	UIManager::GetInstance().AddRootUI(countUI);
	countUI->Load();
	//スタート時のコールバック関数を設定
	countUI->SetStartCallBack([this]()
		{
			EventManager::GetInstance().TriggerEvent(GameEventType::START);
		}
	);

	msgUI_ = std::make_shared<GameMessageUI>(Vector2F(Application::SCREEN_SIZE_X / 2
		, Application::SCREEN_SIZE_Y / 2), Vector2F(400.0f, 100.0f));
	msgUI_->Load();
	msgUI_->Init();

	//プレイヤーのTransformを取得してUIに設定
	setUI_ = [this](std::uint32_t playerID)
	{
		if (distanceUI_) {
			auto actor = actorMng_->FindActorByID(playerID);
			if (actor)
			{
				auto& player = dynamic_cast<UnicyclePlayer&>(*actor);
				distanceUI_->SetTrans(&player.GetTransform());
				distanceUI_->Load();
			}
		}
	};
}

void Unicycle::LoadSE(void)
{
	
}

void Unicycle::InitUI(void)
{
	//メッセージUIの初期化
	msgUI_->SetMassageText(GameMessageUI::MASSAGE_STATE::FINISH, "FINISH!");
	auto player = actorMng_->FindActorsByKind(EntityKind::PLAYER);
	for (auto& p : player)
	{
		auto& player = dynamic_cast<UnicyclePlayer&>(*p);
		setUI_(player.GetEntityID());
	}

	UIManager::GetInstance().AddRootUI(msgUI_);
	ImageUI_->SetChangeSceneCallBack([this]() {
		SceneManager::GetInstance().PushScene(SCENE_ID::PAUSE);
		});
}

void Unicycle::InitSE(void)
{
}

void Unicycle::InitCamera(void)
{
	SceneManager::GetInstance().GetCamera().ChangeMode(Camera::MODE::FOLLOW);
	auto player = actorMng_->FindActorsByKind(EntityKind::PLAYER);
	for (auto& p : player)
	{
		auto& player = dynamic_cast<UnicyclePlayer&>(*p);
		SceneManager::GetInstance().GetCamera().SetFollow(&player.GetTransform());
	}
	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(0.73f, 0.0f, 0.0f));
	SceneManager::GetInstance().GetCamera().StopMove();
}
