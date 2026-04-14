#pragma once
#include<DxLib.h>
#include <chrono>
#include<memory>
#include<list>
#include<map>

#include"../../Application.h"
#include"SceneId.h"

class SceneBase;
class Fader;
class Camera;

class SceneManager
{
public:
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
	void ChangeScene(SCENE_ID scene, std::string editFilename);
	// シーンを新しく積む
	void PushScene(std::shared_ptr<SceneBase>scene);
	void PushScene(SCENE_ID scene);

	// 最後に追加したシーンを削除する。
	void PopScene(void);

	// 強制的に特定のシーンに飛ぶ。リセットをかけ特定のシーンのみにする。
	void JumpScene(std::shared_ptr<SceneBase>scene);
	void JumpScene(SCENE_ID scene);

	// シーンIDの取得
	SCENE_ID GetSceneID(void) { return sceneId_; }



	// デルタタイムの取得
	float GetDeltaTime(void) const { return deltaTime_; }
	// カメラの取得
	Camera* GetCamera(void) const;

private:
	std::list<std::shared_ptr<SceneBase>>scenes_;
	SCENE_ID sceneId_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	// カメラ
	Camera* camera_;

	int mainScreen_;

private:
	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	//３Dの初期化処理
	void Init3D(void);

};

