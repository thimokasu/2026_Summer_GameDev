#include "UIComponent.h"

UIComponent::UIComponent(void)
{
}

UIComponent::UIComponent(Vector2F* size, Vector2F* pos, Vector2F* scale, UI_TYPE type, UI_ANCHOR anchor)
{
	//UIのサイズ、位置、拡大率を設定
	size_ = size;
	pos_ = pos;
	scale_ = *scale;
	//UIのタイプと基準点を設定
	uiType_ = type;
	uiAnchor_ = anchor;
}


UIComponent::~UIComponent(void)
{
}

void UIComponent::GetScreenEdgePos(Vector2F& edgePos) const
{

}
