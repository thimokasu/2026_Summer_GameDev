#pragma once
#include "SceneBase.h"
#include<vector>
#include<map>
#include<string>
#include<functional>
class PauseScene :
	public SceneBase
{
public:
	PauseScene(void);
	~PauseScene(void)override;

    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;

	SCENE_ID GetSceneID(void)const override { return SCENE_ID::PAUSE; }

private:

	int frame_;


	int selectedMenuIndex_ = 0;

	std::vector<std::string> menuItems_;

	std::map<std::string, std::function<void()>> menuActions_;

	std::vector<std::string> yesNoItems_;

	//YES or NO‚Ì‘I‘ðŽˆ‚ð•\Ž¦‚µ‚Ä‚¢‚é‚©
	std::function<void()> execYesAction_;

	bool isYes_ = false;

	std::string yesNoTitle_ = "";


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

	void YesNoUpdate();
	void YesNoDraw();

};

