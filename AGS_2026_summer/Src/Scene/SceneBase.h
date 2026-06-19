#pragma once
#include"../Manager/Game/SceneId.h"
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
	void Load(void);

	// 初期化処理
	void Init(void);

	// 更新ステップ
	void Update(void);

	// 描画処理
	void Draw(void);

	// 解放処理
	void Release(void);

	/// <summary>
	///	シーンIDを取得する
	/// それぞれのシーンでオーバーライドして、シーンIDを返すようにする
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual SCENE_ID GetSceneID(void)const = 0;

protected:
#pragma region 関数
	virtual void SubLoad(void) {};
	virtual void SubInit(void) {};
	virtual void SubUpdate(void) {};
	virtual void SubDraw(void) {};
	virtual void SubRelease(void) {};

	virtual void InitUI(void) {};
	virtual void InitSE(void) {};

#pragma endregion

#pragma region 変数
	// リソース管理
	ResourceManager& resMng_;

	// シーン管理
	SceneManager& sceMng_;
#pragma endregion
};
