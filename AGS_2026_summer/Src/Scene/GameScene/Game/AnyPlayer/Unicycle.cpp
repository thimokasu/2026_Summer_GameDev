#include "Unicycle.h"

#include"../../../../Manager/Game/SceneManager.h"

#include"../../../../Object/Actor/Manager/ActorManager.h"

#include"../../../../Object/Actor/Camera/Camera.h"

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
	SceneManager::GetInstance().GetCamera().SetCameraAngles(VGet(1.18f, 0.0f, 0.0f));
	SceneManager::GetInstance().GetCamera().SetCameraPos(VGet(170.0f, 270.0f, 20.0f));
}
