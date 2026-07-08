#include "Unicycle.h"

#include"../../../../Manager/Game/SceneManager.h"

#include"../../../../Object/Actor/Manager/ActorManager.h"

#include"../../../../Object/Actor/Camera/Camera.h"

#include "../../../../Object/Actor/Charactor/OnePlay/Unicycle/UnicyclePlayer.h"
#include "../../../../Object/UI/FindingJ/GameMessageUI.h"

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
	//ÉJÉÅÉâç¿ïW
	DrawFormatString(0,0,0xffffff,"Camera Position: %f, %f, %f",
		SceneManager::GetInstance().GetCamera().GetPos().x,
		SceneManager::GetInstance().GetCamera().GetPos().y,
		SceneManager::GetInstance().GetCamera().GetPos().z);
	DrawFormatString(0, 20, 0xffffff, "Camera Angles: %f, %f, %f",
		SceneManager::GetInstance().GetCamera().GetAngles().x,
		SceneManager::GetInstance().GetCamera().GetAngles().y,
		SceneManager::GetInstance().GetCamera().GetAngles().z);
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

void Unicycle::SetCollisionCollback(void)
{
}

void Unicycle::SetEventCallBack(void)
{
}

void Unicycle::LoadUI(void)
{
	//auto msgUI = std::make_shared<GameMessageUI>(Vector2F(400.0f, 200.0f), Vector2F(400.0f, 100.0f));
	//UIManager::GetInstance().AddRootUI(msgUI);
	//msgUI->Load();
	//msgUI->SetStartCallBack([this]()
	//	{
	//		EventManager::GetInstance().TriggerEvent(GameEventType::START);
	//	}
	//);
}

void Unicycle::LoadSE(void)
{
}

void Unicycle::InitUI(void)
{
	OnUpdate();
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

}
