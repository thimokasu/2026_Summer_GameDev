#pragma once
#include "../Application.h"
#include "../Common/Vector2.h"
#include "SceneBase.h"
class InputTextArea;

class MultiScene : public SceneBase
{

public:

	// ボタンサイズ
	const int WIDTH = 200;
	const int HEIGHT = 30;

	int HX = Application::SCREEN_SIZE_X / 2;

	// ボタン位置
	const int B1_Y = 415;
	const Vector2 B1_S_POS = Vector2(HX - WIDTH / 2, B1_Y - HEIGHT / 2);
	const Vector2 B1_E_POS = Vector2(HX + WIDTH / 2, B1_Y + HEIGHT / 2);

	const int B2_Y = 455;
	const Vector2 B2_S_POS = Vector2(HX - WIDTH / 2, B2_Y - HEIGHT / 2);
	const Vector2 B2_E_POS = Vector2(HX + WIDTH / 2, B2_Y + HEIGHT / 2);

	// コンストラクタ
	MultiScene(void);

	// デストラクタ
	~MultiScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// タイトル画像
	int imgTitle_;

	// スタート画像
	int imgStart_;

	// IPアドレス
	InputTextArea* inputTextArea1_;
	InputTextArea* inputTextArea2_;
	InputTextArea* inputTextArea3_;
	InputTextArea* inputTextArea4_;

	int imgSpot_;
	int bgm_;
	int val_ = 128;
	float angle_;
	float step_;

};

