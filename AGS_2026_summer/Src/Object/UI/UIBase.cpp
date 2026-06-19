#include "UIBase.h"

UIBase::UIBase(Vector2F pos, Vector2F size)
	: pos_(pos), size_(size), isActive_(true), type_(UITYPE::NONE)
{
}


void UIBase::Load(void)
{
	SubLoad();
	for(auto&child:children_)
	{
		child->Load();
	}
}
void UIBase::Init(void)
{
	SubInit();
	for(auto&child:children_)
	{
		child->Init();
	}
}
void UIBase::Update(void)
{
	if (isActive_ == false)return;
	SubUpdate();
	for(auto&child:children_)
	{
		child->Update();
	}
}
void UIBase::Draw(void)
{
	if (isActive_ == false)return;
	SubDraw();
	for(auto&child:children_)
	{
		child->Draw();
	}
}
void UIBase::Release(void)
{
	SubRelease();
	for(auto&child:children_)
	{
		child->Release();
	}
}

void UIBase::AddChild(std::shared_ptr<UIBase> child)
{
	child->parent_= shared_from_this();
	children_.push_back(child);
}

Vector2F UIBase::GetAbsolutePos(void)
{
	if(auto parentPtr= parent_.lock())
	{
		Vector2F parentPos = parentPtr->GetAbsolutePos();
		return { pos_.x + parentPos.x,pos_.y + parentPos.y };
	}
	return pos_;
}
