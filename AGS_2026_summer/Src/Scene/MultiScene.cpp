#include <string>
#include <DxLib.h>
#include"../Manager/Generic/KeyManager.h"
#include "../Manager/Game/SceneManager.h"
#include "../Net/NetManager.h"
#include "../Manager/Text/InputTextArea.h"
#include "../Utility/AsoUtility.h"
#include "MultiScene.h"


//InputManagerの部分の修正お願いします

MultiScene::MultiScene(void)
{
}

MultiScene::~MultiScene(void)
{
}

void MultiScene::Init(void)
{

	imgTitle_ = LoadGraph("Image/UI/Title.png");
	imgStart_ = LoadGraph("Image/UI/HitStartKey.png");
	imgSpot_ = LoadGraph("Image/UI/SpotLight2.png");

	// 入力エリア
	inputTextArea1_ = new InputTextArea(
		{ B1_E_POS.x + 10, B2_S_POS.y }, { 50, HEIGHT }, 3);
	inputTextArea2_ = new InputTextArea(
		{ B1_E_POS.x + 70, B2_S_POS.y }, { 50, HEIGHT }, 3);
	inputTextArea3_ = new InputTextArea(
		{ B1_E_POS.x + 130, B2_S_POS.y }, { 50, HEIGHT }, 3);
	inputTextArea4_ = new InputTextArea(
		{ B1_E_POS.x + 190, B2_S_POS.y }, { 50, HEIGHT }, 3);

	// デフォルトのホストIPアドレス
	auto hostIp = NetManager::GetInstance().GetHostIp();
	inputTextArea1_->SetText(std::to_string(hostIp.d1));
	inputTextArea2_->SetText(std::to_string(hostIp.d2));
	inputTextArea3_->SetText(std::to_string(hostIp.d3));
	inputTextArea4_->SetText(std::to_string(hostIp.d4));

	bgm_ = LoadSoundMem("Data/retroparty.mp3");

	PlaySoundMem(bgm_, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(val_, bgm_);

	angle_ = step_ = 0.0f;

}

void MultiScene::Update(void)
{

	auto& ins = KeyManager::GetIns();
	if (ins.GetInfo(KEY_TYPE::MOUSE_LEFT).down)
	{

		val_++;
		if (val_ > 255)
		{
			val_ = 255;
		}
		ChangeVolumeSoundMem(val_, bgm_);


		Vector2 moPos;
		GetMousePoint(&moPos.x, &moPos.y);
		
		// ホスト
		if (B1_S_POS.x <= moPos.x && B1_E_POS.x >= moPos.x
			&& B1_S_POS.y <= moPos.y && B1_E_POS.y >= moPos.y)
		{
			NetManager::GetInstance().Run(NET_MODE::HOST);
			SceneManager::GetInstance().ChangeScene(SCENE_ID::CONNECT);
		}

		// クライアント
		if (B2_S_POS.x <= moPos.x && B2_E_POS.x >= moPos.x
			&& B2_S_POS.y <= moPos.y && B2_E_POS.y >= moPos.y)
		{
			IPDATA hostIp;
			hostIp.d1 = std::stoi(inputTextArea1_->GetText());
			hostIp.d2 = std::stoi(inputTextArea2_->GetText());
			hostIp.d3 = std::stoi(inputTextArea3_->GetText());
			hostIp.d4 = std::stoi(inputTextArea4_->GetText());
			NetManager::GetInstance().SetHostIp(hostIp);
			NetManager::GetInstance().Run(NET_MODE::CLIENT);
			SceneManager::GetInstance().ChangeScene(SCENE_ID::CONNECT);
		}

	}

	inputTextArea1_->Update();
	inputTextArea2_->Update();
	inputTextArea3_->Update();
	inputTextArea4_->Update();

}

void MultiScene::Draw(void)
{

	// 背景
	DrawGraph(0, 0, imgTitle_, true);

	// ネットワーク情報背景
	DrawBox(
		0, B1_S_POS.y - 10, 
		Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0x000000, true);

	// ホスト
	DrawBox(B1_S_POS.x, B1_S_POS.y, B1_E_POS.x, B1_E_POS.y, 0xffffff, false);
	DrawString(B1_S_POS.x + 50, B1_S_POS.y + 7, "HOST", 0xffffff);

	// クライアント
	DrawBox(B2_S_POS.x, B2_S_POS.y, B2_E_POS.x, B2_E_POS.y, 0xffffff, false);
	DrawString(B2_S_POS.x + 50, B2_S_POS.y + 7, "CLIENT", 0xffffff);

	// ホストIPアドレス
	DrawBox(B1_E_POS.x + 10, B1_S_POS.y, B1_E_POS.x + 30, B1_E_POS.y, 0x000000, true);
	DrawString(B1_E_POS.x + 12, B1_S_POS.y + 12, "ホストのIPアドレス", 0xffffff);
	inputTextArea1_->Draw();
	inputTextArea2_->Draw();
	inputTextArea3_->Draw();
	inputTextArea4_->Draw();


	step_ += 1.0f * 0.02f;
	angle_ = sinf(step_) * 15.0f * DX_PI_F / 180.0f;
	SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
	//DrawRotaGraph(
	//	Application::SCREEN_SIZE_X / 2,
	//	Application::SCREEN_SIZE_Y / 2, 
	//	1.0, angle_, imgSpot_, true);

	DrawRotaGraph2(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 - 150,
		150, 0,
		1.0, angle_, imgSpot_, true);


	angle_ = sinf(step_ * 1.2f) * 15.0f * DX_PI_F / 180.0f;
	DrawRotaGraph2(
		Application::SCREEN_SIZE_X / 2 - 100,
		Application::SCREEN_SIZE_Y / 2 - 150,
		150, 0,
		1.0, angle_, imgSpot_, true);

	angle_ = sinf(step_ * -1.3f) * 15.0f * DX_PI_F / 180.0f;
	DrawRotaGraph2(
		Application::SCREEN_SIZE_X / 2 + 100,
		Application::SCREEN_SIZE_Y / 2 - 150,
		150, 0,
		1.0, angle_, imgSpot_, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void MultiScene::Release(void)
{

	DeleteGraph(imgTitle_);
	DeleteGraph(imgStart_);
	DeleteGraph(imgSpot_);

	inputTextArea1_->Release();
	delete inputTextArea1_;
	inputTextArea2_->Release();
	delete inputTextArea2_;
	inputTextArea3_->Release();
	delete inputTextArea3_;
	inputTextArea4_->Release();
	delete inputTextArea4_;

}
