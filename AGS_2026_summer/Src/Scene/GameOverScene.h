#pragma once
#include "SceneBase.h"

#include<vector>
#include<memory>
class SceneBase;

class GameOverScene :
    public SceneBase

{
	

public:
	GameOverScene(void);
	~GameOverScene(void);

	static std::shared_ptr<GameOverScene> Create(void);
	virtual void SubLoad(void) override;
	virtual void SubInit(void) override;
	virtual void SubUpdate(void) override;
	virtual void SubDraw(void) override;
	virtual void SubRelease(void) override;
	virtual SCENE_ID GetSceneID(void)const override { return SCENE_ID::GAMEOVER; }




};

