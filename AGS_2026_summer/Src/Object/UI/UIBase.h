#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include"../../Common/Vector2.h"
#include "UIType.h"
#include"UIName.h"

class UIBase : public std::enable_shared_from_this<UIBase>
{
public:
	UIBase(Vector2F pos, Vector2F size);
	virtual ~UIBase() = default;

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void AddChild(std::shared_ptr<UIBase> child);

	Vector2F GetAbsolutePos(void);

#pragma region セッター・ゲッター
	void SetPos(Vector2F pos) { pos_ = pos; }
	void GetPos(Vector2F& pos) { pos = pos_; }
	void SetSize(Vector2F size) { size_ = size; }
	void GetSize(Vector2F& size) { size = size_; }
	void SetActive(bool isActive) { isActive_ = isActive; }
	bool GetActive(void) { return isActive_; }
	UINAME GetUIName(void) { return uiName_; }
#pragma endregion
protected:
#pragma region 関数
	virtual void SubLoad(void) {};
	virtual void SubInit(void){};
	virtual	void SubUpdate(void){};
	virtual void SubDraw(void){};
	virtual void SubRelease(void){};
#pragma endregion

#pragma region 変数
	UITYPE type_;
	UINAME uiName_;
	Vector2F pos_;
	Vector2F size_;
	bool isActive_;
	std::weak_ptr<UIBase>parent_;
	std::vector<std::shared_ptr<UIBase>> children_;
	int handleId_;
#pragma endregion
};