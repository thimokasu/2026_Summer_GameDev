#include "SceneBase.h"
#include"../Manager/Resource/ResourceManager.h"
#include"../Manager/Game/SceneManager.h"
#include"../Manager/Generic/KeyManager.h"
#include"../Application.h"

SceneBase::SceneBase(void) :
	resMng_(ResourceManager::GetInstance()),
	sceMng_(SceneManager::GetInstance())
{
}

SceneBase::~SceneBase(void)
{
}


// 読み込み
void SceneBase::Load(void)
{
	SubLoad();
}

// 初期化処
void SceneBase::Init(void)
{
	SubInit();
	InitUI();
	InitSE();
}

// 更新ステッ
void SceneBase::Update(void)
{
	if (SceneManager::GetInstance().GetSceneID() != SCENE_ID::PAUSE)
	{
		//エスケープ押したらメニューシーンへ
		if (KeyManager::GetIns().GetInfo(KEY_TYPE::PAUSE).down)
		{
			SceneManager::GetInstance().PushScene(SCENE_ID::PAUSE);
			return;
		}
	}
	SubUpdate();
}

// 描画処
void SceneBase::Draw(void)
{
	SubDraw();
}

// 解放処
void SceneBase::Release(void)
{
	SubRelease();
}
