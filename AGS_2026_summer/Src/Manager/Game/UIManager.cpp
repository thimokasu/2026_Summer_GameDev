#include "UIManager.h"
#include "../../Application.h"
#include "../../Object/UI/UIBase.h"

UIManager* UIManager::instance_ = nullptr;

void UIManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new UIManager();
	}
}

UIManager& UIManager::GetInstance(void)
{
	return *instance_;
}

void UIManager::DeleteInstance(void)
{
	if (instance_ != nullptr)
	{
		instance_->Clear();
		delete instance_;
		instance_ = nullptr;
	}
}

// コンストラクタの実体
UIManager::UIManager(void)
{
}

void UIManager::Load(void)
{
	for (auto& ui : rootUIList_)
	{
		ui->Load();
	}
}

void UIManager::Init(void)
{
	for (auto& ui : rootUIList_)
	{
		ui->Init();
	}
}

void UIManager::Update(void)
{
	for (auto& ui : rootUIList_)
	{
		ui->Update();
	}
}

void UIManager::Draw(void)
{
	for (auto& ui : rootUIList_)
	{
		ui->Draw();
	}
}

void UIManager::Clear(void)
{
	for (auto& ui : rootUIList_)
	{
		ui->Release();
	}
	rootUIList_.clear();
}

void UIManager::AddRootUI(std::shared_ptr<UIBase> ui)
{
	if (!ui) return; // 安全のための防衛コード
	rootUIList_.push_back(ui);
}