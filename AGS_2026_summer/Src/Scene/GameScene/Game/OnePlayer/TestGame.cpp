#include "TestGame.h"

TestGame::TestGame(ActorManager* actMng, CollisionManager* colMng)
	:GameBase(actMng,colMng)
{
}

TestGame::~TestGame(void)
{
}

void TestGame::SubLoad(void)
{
}

void TestGame::SubInit(void)
{
	isUpdate_ = true;
}

void TestGame::SubUpdate(void)
{
}

void TestGame::SubDraw(void)
{
}

void TestGame::SubRelease(void)
{
}

void TestGame::SetContactEventRule(void)
{
}

void TestGame::SetContactEventCallback(void)
{
}



void TestGame::SetEventCallBack(void)
{
}

void TestGame::LoadUI(void)
{
}

void TestGame::LoadSE(void)
{
}

void TestGame::InitUI(void)
{
}

void TestGame::InitSE(void)
{
}

void TestGame::InitCamera(void)
{
}
