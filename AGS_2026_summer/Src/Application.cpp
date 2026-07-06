#include <DxLib.h>
#include<EffekseerForDXLib.h>
#include "Application.h"

#include "Manager/Game/SceneManager.h"
#include"Manager/Generic/KeyManager.h"

#include"Scene/TitleScene.h"
#include"Scene/GameScene/GameScene.h"
#include"Scene/PauseScene.h"
#include"Scene/GameSelect/GameSelectScene.h"
#include"Scene/GameResultScene.h"

Application* Application::instance_ = nullptr;

const std::string Application::PATH_DATA = "Data/";
const std::string Application::PATH_IMAGE = PATH_DATA + "Image/";
const std::string Application::PATH_MODEL = PATH_DATA + "Model/";
const std::string Application::PATH_EFFECT = PATH_DATA + "Effect/";
const std::string Application::PATH_ANIMATION = PATH_DATA + "Animation/";

void Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::DeleteInstance(void)
{
	if (instance_ != nullptr)
	{
		instance_->Destroy();
		delete instance_;
		instance_ = nullptr;
	}
}

void Application::Init(void)
{

	// アプリケーションの初期設定
	SetWindowText("2416043_山﨑佑斗");

	// ウィンドウサイズ
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	// ２重起動検査回避用
	SRand(GetNowCount());
	int rand = GetRand(999);
	std::string name = "UDP Test";
	name += std::to_string(rand);
	SetMainWindowClassName(name.c_str());
	SetAlwaysRunFlag(true);

	// DxLibの初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}
	//エフェクシアの初期化
	InitEffekseer();

	// 乱数のシード値を設定する
	DATEDATA date;

	// 現在時刻を取得する
	GetDateTime(&date);

	// 乱数の初期値を設定する
	// 設定する数値によって、ランダムの出方が変わる
	SRand(date.Year + date.Mon + date.Day + date.Hour + date.Min + date.Sec);

	// 入力制御初期化
	SetUseDirectInputFlag(true);
	KEY::CreateIns();


	// シーン管理初期化
	SceneManager::CreateInstance();
	SceneManager::GetInstance().SetSceneFactory(SCENE_ID::TITLE, []() { return std::make_shared<TitleScene>(); });
	SceneManager::GetInstance().SetSceneFactory(SCENE_ID::GAME, []() {return std::make_shared<GameScene>(); });
	SceneManager::GetInstance().SetSceneFactory(SCENE_ID::PAUSE, []() {return std::make_shared<PauseScene>(); });
	SceneManager::GetInstance().SetSceneFactory(SCENE_ID::GAME_SELECT, []() {return std::make_shared<GameSelectScene>(); });
	SceneManager::GetInstance().SetSceneFactory(SCENE_ID::RESULT, []() {return std::make_shared<GameResultScene>(); });
	SceneManager::GetInstance().Init();
	// ネットワーク管理初期化
}

void Application::Run(void)
{

	auto& keymanager = KEY::GetIns();
	auto&sceneManager = SceneManager::GetInstance();

	// ゲームループ
	while (ProcessMessage() == 0 && !isRequestedExit_)
	{

		keymanager.Update();
		sceneManager.Update();
		sceneManager.Draw();

		ScreenFlip();

	}

}

void Application::Destroy(void)
{

	// シーン管理解放
	SceneManager::GetInstance().Destroy();

	// 入力制御解放
	KeyManager::GetIns().DeleteIns();


	Effkseer_End();

	// DxLib終了
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}

}

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}

Vector2 Application::GetWindowSize(void) const
{
	return Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

void Application::RequestExit(void)
{
	isRequestedExit_ = true;
}


Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
	isRequestedExit_ = false;
}

void Application::InitEffekseer(void)
{
	if (Effekseer_Init(8000) == -1) {
		DxLib_End();
	}
}
