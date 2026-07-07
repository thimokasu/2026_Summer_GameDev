#include "SceneManager.h"

#include <chrono>
#include <DxLib.h>
#include<EffekseerForDXLib.h>

#include"../../Scene/SceneBase.h"

#include"SE.h"
#include"UIManager.h"
#include"../../Manager/Generic/Loading.h"
#include"../../Manager/System/EventSystem/EventManager.h"

#include"../Resource/ResourceManager.h"

#include"../../Object/Actor/Camera/Camera.h"


SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
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



void SceneManager::SetSceneFactory(SCENE_ID sceneID, SceneFactory factory)
{
	sceneFactories_[sceneID] = factory;
}

void SceneManager::Init(void)
{
	sceneID_ = SCENE_ID::TITLE;
	// ロード画面生成
	Loading::GetInstance()->CreateInstance();
	Loading::GetInstance()->Init();
	Loading::GetInstance()->Load();

	// カメラ
	camera_ = std::make_unique<Camera>();
	camera_->Init();
	//リソースマネージャー
	ResourceManager::CreateInstance();
	ResourceManager::GetInstance().Init();
	//UIマネージャー
	UIManager::CreateInstance();
	UIManager::GetInstance().Init();
	//イベントマネージャー
	EventManager::CreateInstance();

	//３D用の設定
	Init3D();

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	// 初期シーンの設定
	ChangeScene(SCENE_ID::TITLE);

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
		UIManager::GetInstance().Update();
		EventManager::GetInstance().Update();
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
	//UI
	UIManager::GetInstance().Draw();

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

	DeleteGraph(mainScreen_);

	// ロード画面の削除
	Loading::GetInstance()->Release();
	Loading::GetInstance()->DeleteInstance();
		EventManager::DeleteInstance();
		UIManager::DeleteInstance();

	// インスタンスのメモリ解放
	delete instance_;
	instance_ = nullptr;
}

void SceneManager::ChangeScene(std::shared_ptr<SceneBase>_scene)
{
	if (scenes_.empty())
	{
		scenes_.push_back(_scene);
	}
	else
	{
		UIManager::GetInstance().Clear();
		ResourceManager::GetInstance().Release();
		EventManager::GetInstance().Clear();
		scenes_.back()->Release();
		scenes_.back() = _scene;
	}
	scenes_.back()->Load();
	scenes_.back()->Init();
	UIManager::GetInstance().Init();
	sceneID_ = scenes_.back()->GetSceneID();
}

void SceneManager::ChangeScene(SCENE_ID scene)
{
	auto it = sceneFactories_.find(scene);
	if (it != sceneFactories_.end())
	{
		sceneID_ = scene;
		//登録されたラムダ式を実行して実体を生成
		ChangeScene(it->second());
	}
}


	void SceneManager::PushScene(std::shared_ptr<SceneBase> scene)
	{
		//新しく積むのでもともと入っている奴はまだ削除されない
		scenes_.push_back(scene);
		scenes_.back()->Load();
		scenes_.back()->Init();
		UIManager::GetInstance().Init();
		sceneID_ = scenes_.back()->GetSceneID();

	}

	void SceneManager::PushScene(SCENE_ID scene)
	{
		auto it = sceneFactories_.find(scene);
		if (it != sceneFactories_.end())
		{
			sceneID_ = scene;
			//登録されたラムダ式を実行して実体を生成
			PushScene(it->second());
		}
	}

	void SceneManager::PopScene(void)
	{
		//積んであるものを消して、もともとあったものを末尾にする
		if (scenes_.size() > 1)
		{
			scenes_.back()->Release();
			scenes_.pop_back();
			sceneID_ = scenes_.back()->GetSceneID();
		}

	}

	void SceneManager::ResetScene(std::shared_ptr<SceneBase> scene)
	{
		// 全て解放
		for (auto& scene : scenes_) { scene->Release(); }
		scenes_.clear();
		scenes_.push_back(scene);

		// 新しく積む
		ChangeScene(scene);

	}

	void SceneManager::JumpScene(std::shared_ptr<SceneBase> scene)
	{
		UIManager::GetInstance().Clear();
		ResourceManager::GetInstance().Release();
		EventManager::GetInstance().Clear();
		// 全て解放
		for (auto& scene : scenes_) { scene->Release(); }
		scenes_.clear();

		// 新しく積む
		ChangeScene(scene);
	}

	void SceneManager::JumpScene(SCENE_ID scene)
	{
		auto it = sceneFactories_.find(scene);
		if (it != sceneFactories_.end())
		{
			UIManager::GetInstance().Clear();
			ResourceManager::GetInstance().Release();
			EventManager::GetInstance().Clear();
			for (auto& s : scenes_) { s->Release(); }
			scenes_.clear();
			ChangeScene(it->second());
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

	Camera& SceneManager::GetCamera(void) const
	{
		return *camera_;
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
