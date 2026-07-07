#pragma once
#include<DxLib.h>
#include <chrono>
#include<memory>
#include<list>
#include<map>
#include<functional>

#include"../../Application.h"
#include"SceneId.h"

class SceneBase;
class Fader;
class Camera;

class SceneManager
{
public:
	//シーン生成用の関数オブジェクト
	using SceneFactory = std::function<std::shared_ptr<SceneBase>()>;

	// シングルトン（生成・取得・削除）
	static void CreateInstance(void);
	static SceneManager& GetInstance(void);
	static void DeleteInstance(void);
private:
	// 静的インスタンス
	static SceneManager* instance_;
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// コピーコンストラクタも同様
	SceneManager(const SceneManager& instance) = default;
	// デストラクタも同様
	~SceneManager(void) = default;

public:
	// 外部からシーンの生成レシピを登録するための関数
	void SetSceneFactory(SCENE_ID sceneID, SceneFactory factory);

	// 初期化
	void Init(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// リソースの破棄
	void Destroy(void);

	// 状態遷移
	void ChangeScene(std::shared_ptr<SceneBase>scene);
	void ChangeScene(SCENE_ID scene);
	template<typename SceneType, typename...Args>
	void ChangeScene(Args&&...args);

	// シーンを新しく積む
	void PushScene(std::shared_ptr<SceneBase>scene);
	void PushScene(SCENE_ID scene);

	// 最後に追加したシーンを削除する。
	void PopScene(void);
	void ResetScene(std::shared_ptr<SceneBase>scene);

	// 強制的に特定のシーンに飛ぶ。リセットをかけ特定のシーンのみにする。
	void JumpScene(std::shared_ptr<SceneBase>scene);
	void JumpScene(SCENE_ID scene);

	// シーンIDの取得
	SCENE_ID GetSceneID(void) { return sceneID_; }

	// デルタタイムの取得
	float GetDeltaTime(void) const { return deltaTime_; }

	float GetTotalGameTime(void);

	void SetTotalGameTime(float time);

	void ForwardGameTime(void);

	// カメラの取得
	Camera& GetCamera(void) const;

private:
#pragma region 変数
	//シーンのレシピを管理するマップ
	std::map<SCENE_ID, SceneFactory>sceneFactories_;
	//現在のシーンの実体を管理するリスト
	std::list<std::shared_ptr<SceneBase>> scenes_;
	SCENE_ID sceneID_;
	//ゲームの総時間
	float totalGameTime_;
	//デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	//カメラ
	std::unique_ptr<Camera> camera_;
	int mainScreen_;
#pragma endregion

#pragma region 関数
	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	//３Dの初期化処理
	void Init3D(void);
#pragma endregion

};
/// <summary>
/// 無限引数によるシーンの変更
/// </summary>
/// <typeparam name="SceneType"></typeparam>
/// <typeparam name="...Args"></typeparam>
/// <param name="...args"></param>
/// 使い方
/// SceneManager::Getinstance().ChangeScene<変更したいシーン>(引数)
template<typename SceneType, typename ...Args>
inline void SceneManager::ChangeScene(Args && ...args)
{
	auto nextScene = std::make_shared<SceneType>(std::forward<Args>(args)...);
	ChangeScene(nextScene);
}
