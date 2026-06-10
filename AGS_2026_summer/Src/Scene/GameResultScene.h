#pragma once
#include "SceneBase.h"

class GameResultScene : public SceneBase
{

public:

	GameResultScene(void);
	~GameResultScene(void)override;

	// 読み込み
	void Initialize();

	// 更新ステップ
	void Update()override;
	
	// 描画ステップ
	void Draw()override;

};

