#include "TitleScene.h"
#include"../Manager/Game/SceneManager.h"
#include"../Manager/Generic/KeyManager.h"
#include"../Manager/Resource/ResourceManager.h"


TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::SubLoad(void)
{
	imgTitle_ = LoadGraph("Data/Image/titleBackGound.png");
	logo_ = LoadGraph("Data/Image/titleLogo.png");
	
}

void TitleScene::SubInit(void)
{
	
}

void TitleScene::SubUpdate(void)
{
	//スペース押したらゲームシーンへ
	if (KeyManager::GetIns().GetInfo(KEY_TYPE::ENTER).down)
	{
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME_SELECT);
		return;
	}
	// ロゴの揺れ用角度を更新（値を変えると速さが変わります）
	angle_ += 0.01f;
}

void TitleScene::SubDraw(void)
{
    DrawGraph(0, 0, imgTitle_, TRUE);

    // sin波を使ってY座標をオフセットする
    // sin(angle_) は -1.0 から 1.0 の間を動く
    // 20.0 を掛けることで、上下に 20ピクセルずつ揺れる
    float offsetY = sinf(angle_) * 20.0f;

    // Y座標の中心 (Application::SCREEN_SIZE_Y / 2) に offsetY を加える
    DrawRotaGraph(
        Application::SCREEN_SIZE_X / 2,
        Application::SCREEN_SIZE_Y / 2 + (int)offsetY,
        0.5f,
        0,
        logo_,
        true
    );

    DrawGraph(600, 700, imgPush_, TRUE);
}

void TitleScene::SubRelease(void)
{
}
