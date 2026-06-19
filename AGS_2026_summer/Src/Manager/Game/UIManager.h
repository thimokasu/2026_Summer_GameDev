#pragma once
#include<memory>
#include<vector>
#include"../../Object/UI/UIName.h"

class UIBase;

class UIManager
{
public	:
	static void CreateInstance(void);
	static UIManager& GetInstance(void);
	static void DeleteInstance(void);
private:
	static UIManager* instance_;
	UIManager(void);
	UIManager(const UIManager& instance) = default;
	~UIManager(void) = default;
public:
	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Clear(void);
	//最上位のUIを画面に追加する関数
	void AddRootUI(std::shared_ptr<UIBase> ui);

	template<typename T>
	std::shared_ptr<T> GetUI(UINAME name);

private:
	//画面上に存在するUIのルートを管理するリスト
	std::vector<std::shared_ptr<UIBase>> rootUIList_;
};

template<typename T>
std::shared_ptr<T> UIManager::GetUI(UINAME name)
{
	for (auto& ui : rootUIList_)
	{
		if (ui->GetUIName() == name)
		{
			return std::dynamic_pointer_cast<T>(ui);
		}
	}
	return nullptr;
}
