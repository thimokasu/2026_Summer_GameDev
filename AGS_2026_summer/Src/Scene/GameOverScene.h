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
	virtual void Load(void) override;
	virtual void Init(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	virtual void Release(void) override;
	virtual SCENE_ID GetSceneID(void)const override { return SCENE_ID::GAMEOVER; }




};

