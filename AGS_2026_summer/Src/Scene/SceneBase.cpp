#include "SceneBase.h"
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Game/SceneManager.h"
#include"../Application.h"

SceneBase::SceneBase(void) :
	resMng_(ResourceManager::GetInstance()),
	sceMng_(SceneManager::GetInstance())
{
}

SceneBase::~SceneBase(void)
{
}
