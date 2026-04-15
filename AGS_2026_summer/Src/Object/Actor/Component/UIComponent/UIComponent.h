#pragma once
#include "../ComponentBase.h"
#include<DxLib.h>

#include"../../../../Common/Vector2.h"
class UIComponent :
    public ComponentBase
{
public:
	
	enum class UI_TYPE
	{
		NONE = -1,
		SCREEN,			//画面に貼り付けるUI
		WORLD,			//ワールド空間に配置するUI
		MAX,
	};

	//UIの基準点
	enum class UI_ANCHOR
	{
		TOP_LEFT,		//左上
		TOP_RIGHT,		//右上
		CENTER,			//中央
		BOTTOM_LEFT,	//左下
		BOTTOM_RIGHT,	//右下
	};

public:
	UIComponent(void);
	UIComponent(Vector2F* size, Vector2F* pos, Vector2F* scale, UI_TYPE uiType, UI_ANCHOR anchor=UI_ANCHOR::TOP_LEFT);
	~UIComponent(void) override;

	void OffActive(void) { isActive_ = false; }
	void OnActive(void) { isActive_ = true; }
	bool IsActive(void) const { return isActive_; }

	// UIのタイプの設定
	void SetUIType(UI_TYPE type) { uiType_ = type; }
	// UIの基準点の設定
	void SetUIAnchor(UI_ANCHOR anchor) { uiAnchor_ = anchor; }

	void SetPos(Vector2F* pos) { pos_ = pos; }
	void SetScale(const Vector2F& scale) { scale_ = scale; }

	void GetPos(Vector2F& pos) const { pos = *pos_; }
	//UIの画面端の位置を取得
	void GetScreenEdgePos(Vector2F& edgePos) const;

	// UIの編集可能状態の設定
	void OffEditable(void) { isEditable_ = false; }
	void OnEditable(void) { isEditable_ = true; }
	bool IsEditable(void) const { return isEditable_; }

private:
	
	int uiId_ = -1;//使用するUIのハンドル番号
	Vector2F* size_;
	Vector2F* pos_;
	VECTOR* pos3D_;

	Vector2F scale_ = { 1.0f,1.0f };//UIの拡大率
	bool isActive_ = true;//UIの有効状態

	UI_TYPE uiType_ = UI_TYPE::NONE;//UIのタイプ
	UI_ANCHOR uiAnchor_ = UI_ANCHOR::TOP_LEFT;//UIの基準点
	bool isEditable_ = false;		//UIの編集可能状態
};

