#include "SceneManager.h"

#include <chrono>
#include <DxLib.h>
#include<EffekseerForDXLib.h>

#include"../../Scene/SceneBase.h"
#include"../../Scene/TitleScene.h"
#include"../../Scene/GameScene.h"
#include "../../Scene/MultiScene.h"
#include "../../Scene/ConnectScene.h"

#include"../../Manager/Generic/Loading.h"
#include"../Resource/ResourceManager.h"

#include"../../Object/Actor/Camera/Camera.h"


SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::DeleteInstance(void)
{
	if (instance_ != nullptr)
	{
		instance_->Destroy();
		delete instance_;
		instance_ = nullptr;
	}
}

SceneManager::SceneManager(void)
{

}



void SceneManager::Init(void)
{
	sceneId_ = SCENE_ID::TITLE;
	// ロード画面生成
	Loading::GetInstance()->CreateInstance();
	Loading::GetInstance()->Init();
	Loading::GetInstance()->Load();

	// カメラ
	camera_ = new Camera();
	camera_->Init();

	ResourceManager::CreateInstance();
	ResourceManager::GetInstance().Init();

	//３D用の設定
	Init3D();

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	// 初期シーンの設定
	ChangeScene(SCENE_ID::GAME);

	mainScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
}
void SceneManager::Update(void)
{
	//シーンがなければ終了
	if (scenes_.empty()) { return; }

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	if (Loading::GetInstance()->IsLoading())
	{
		Loading::GetInstance()->Update();
		if (Loading::GetInstance()->IsLoading() == false)
		{
			scenes_.back()->Init();
		}
	}
	else
	{
		scenes_.back()->Update();
	}
	camera_->Update();

}

void SceneManager::Draw(void)
{
	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(mainScreen_);

	// 画面を初期化
	ClearDrawScreen();

	//エフェクシアの更新
	UpdateEffekseer3D();

	if (Loading::GetInstance()->IsLoading())
	{
		Loading::GetInstance()->Draw();
	}
	else
	{
		camera_->SetBeforeDraw();
		for (auto& scene : scenes_)
		{
			scene->Draw();
		}
	}
	//エフェクシアの描画
	DrawEffekseer3D();
	// カメラ描画
	camera_->DrawDebug();

	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1, 0, mainScreen_, true);
}

void SceneManager::Destroy(void)
{
	// シーンの解放
		//全てのシーンの解放・削除
	for (auto& scene : scenes_) { scene->Release(); }
	scenes_.clear();

	//カメラの解放
	camera_->Release();
	delete camera_;

	DeleteGraph(mainScreen_);

	// ロード画面の削除
	Loading::GetInstance()->Release();
	Loading::GetInstance()->DeleteInstance();


	// インスタンスのメモリ解放
	delete instance_;
	instance_ = nullptr;
}

void SceneManager::ChangeScene(std::shared_ptr<SceneBase>_scene)
{
	// シーンが空か？
	if (scenes_.empty())
	{
		//空なので新しく入れる
		scenes_.push_back(_scene);
	}
	else
	{
		//末尾のものを新しい物に入れ替える
		ResourceManager::GetInstance().Release();
		scenes_.back()->Release();
		scenes_.back() = _scene;

	
	}

	// 読み込み(非同期)
	Loading::GetInstance()->StartAsyncLoad();
	scenes_.back()->Load();
	Loading::GetInstance()->EndAsyncLoad();

}

void SceneManager::ChangeScene(SCENE_ID scene)
{
	switch (scene)
	{
	case SCENE_ID::TITLE:
		ChangeScene(std::make_shared<TitleScene>());
		break;
	case SCENE_ID::GAME:
		ChangeScene(std::make_shared<GameScene>());
		break;
	case SCENE_ID::MULTI:
		ChangeScene(std::make_shared<MultiScene>());
		break;
	case SCENE_ID::CONNECT:
		ChangeScene(std::make_shared<ConnectScene>());
		break;
	default:
		break;
	}
}


	void SceneManager::ChangeScene(SCENE_ID scene, std::string editFilename)
	{
		switch (scene)
		{
		case SCENE_ID::TITLE:
			ChangeScene(std::make_shared<TitleScene>());
			break;
		case SCENE_ID::GAME:
			ChangeScene(std::make_shared<GameScene>());
			break;
		default:
			break;
		}
	}

	void SceneManager::PushScene(std::shared_ptr<SceneBase> scene)
	{
		//新しく積むのでもともと入っている奴はまだ削除されない
		scenes_.push_back(scene);
		scenes_.back()->Load();
		scenes_.back()->Init();
	}

	void SceneManager::PushScene(SCENE_ID scene)
	{

	}

	void SceneManager::PopScene(void)
	{
		//積んであるものを消して、もともとあったものを末尾にする
		if (scenes_.size() > 1)
		{
			scenes_.back()->Release();
			scenes_.pop_back();
		}
	}

	void SceneManager::JumpScene(std::shared_ptr<SceneBase> scene)
	{
		// 全て解放
		for (auto& scene : scenes_) { scene->Release(); }
		scenes_.clear();

		// 新しく積む
		ChangeScene(scene);
	}

	void SceneManager::JumpScene(SCENE_ID scene)
	{
		switch (scene)
		{
		case SCENE_ID::TITLE:
			ChangeScene(std::make_shared<TitleScene>());
			break;
		case SCENE_ID::GAME:
			ChangeScene(std::make_shared<GameScene>());
			break;
		default:
			break;
		}
	}

	float SceneManager::GetTotalGameTime(void)
	{
		return totalGameTime_;
	}

	void SceneManager::SetTotalGameTime(float time)
	{
		totalGameTime_ = time;
	}

	void SceneManager::ForwardGameTime(void)
	{
		totalGameTime_ += GetDeltaTime();
	}

	Camera* SceneManager::GetCamera(void) const
	{
		return camera_;
	}


	void SceneManager::ResetDeltaTime(void)
	{
		deltaTime_ = 0.016f;
		preTime_ = std::chrono::system_clock::now();
	}

	void SceneManager::Init3D(void)
	{
		// 背景色設定
		SetBackgroundColor(0, 139, 139);
		// Zバッファを有効にする
		SetUseZBuffer3D(true);
		// Zバッファへの書き込みを有効にする
		SetWriteZBuffer3D(true);
		// バックカリングを有効にする
		SetUseBackCulling(true);
		// ライトを有効にする
		SetUseLighting(true);
		// ディレクショナルライト方向の設定(正規化されていなくても良い)
		// 正面から斜め下に向かったライト
		ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });

		//// フォグ設定
		//SetFogEnable(true);
		//// フォグの色
		//SetFogColor(100, 100, 100);
		//// フォグを発生させる奥行きの最小、最大距離
		//SetFogStartEnd(500 , 5000 );

	}
