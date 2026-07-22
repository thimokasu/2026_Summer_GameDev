#include "DropperDrop.h"
#include"../../../../../../Manager/System/EventSystem/EventManager.h"
#include"DropperIdle.h"
void DropperDrop::EnterT(Dropper* owner)
{
	isLoop_ = true;
	EventManager::GetInstance().TriggerEvent(GameEventType::CREATE_SPIKE);
	owner->ChangeState<DropperIdle>();
}

void DropperDrop::HandleInputT(Dropper* owner)
{
}

void DropperDrop::UpdateT(Dropper* owner)
{
}

void DropperDrop::ExitT(Dropper* owner)
{
}
