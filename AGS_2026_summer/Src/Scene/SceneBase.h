#pragma once
class ResourceManager;
class SceneManager;
class SceneBase
{

public:

	// コンストラクタ
	SceneBase(void);

	// デストラクタ
	virtual ~SceneBase(void);

	// 読み込み
	virtual void Load(void) {};

	// 初期化処理
	virtual void Init(void) {};

	// 更新ステップ
	virtual void Update(void) {};

	// 描画処理
	virtual void Draw(void) {};

	// 解放処理
	virtual void Release(void) {};



protected:

	// リソース管理
	ResourceManager& resMng_;

	// シーン管理
	SceneManager& sceMng_;
};
