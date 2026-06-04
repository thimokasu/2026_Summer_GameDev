#pragma once
#include "SceneBase.h"
#include<vector>
#include<map>
#include<string>
class PauseScene :
    public SceneBase
{
public:
    PauseScene(void);
    ~PauseScene(void)override;

    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;

	SCENE_ID GetSceneID(void)const override { return SCENE_ID::PAUSE; }

private:
    int frame_;

	int selectedMenuIndex_ = 0;

	std::vector<std::string> menuItems_;

	using Update_t = void(PauseScene::*)(void);
	using Draw_t = void(PauseScene::*)(void);

    Update_t update_;
	Draw_t draw_;

	void AppearUpdate();
	void NormalUpdate();
	void DisappearUpdate();
	void ExpandDraw(); 
	void NormalDraw();
	void DrawFrame(float rate);

	void DrawMenu();

};



