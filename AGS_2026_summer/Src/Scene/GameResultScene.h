#pragma once
#include "SceneBase.h"

class GameResultScene : public SceneBase
{

public:

	GameResultScene(void);
	~GameResultScene(void)override;


	void Init();
	void Update()override;
	void Draw()override;
	void Load(void)override;
	void Release(void)override;
	SCENE_ID GetSceneID(void)const override { return SCENE_ID::RESULT; }


};


