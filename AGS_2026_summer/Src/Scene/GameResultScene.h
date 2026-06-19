#pragma once
#include "SceneBase.h"

class GameResultScene : public SceneBase
{

public:

	GameResultScene(void);
	~GameResultScene(void)override;

	void SubLoad()override;
	void SubInit()override;
	void SubUpdate()override;
	void SubDraw()override;
	void SubRelease(void)override;
	SCENE_ID GetSceneID(void)const override { return SCENE_ID::RESULT; }


};


