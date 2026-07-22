#include "SpikeDrop.h"
#include"../../../../../Object/Actor/Item/SpikeDrop/Spike.h"
#include"../../../../../Object/Actor/Charactor/OneVsThree/SpikeDrop/Dropper.h"
#include"../../../../../Object/Actor/Manager/ActorManager.h"
#include"../../../../../Object/Actor/Charactor/OneVsThree/SpikeDrop/SpikeDropPlayer.h"
#include"../../../../../Object/Actor/Charactor/OneVsThree/SpikeDrop/State/SpikeDropPlayerHit.h"
SpikeDrop::SpikeDrop(ActorManager* actMng, CollisionManager* colMng):GameBase(actMng,colMng)
{
}

SpikeDrop::~SpikeDrop(void)
{
}

void SpikeDrop::SubLoad(void)
{
}

void SpikeDrop::SubInit(void)
{
	isUpdate_ = true;
}

void SpikeDrop::SubUpdate(void)
{
}

void SpikeDrop::SubDraw(void)
{
}

void SpikeDrop::SubRelease(void)
{
}

void SpikeDrop::SetContactEventRule(void)
{
	EventManager::GetInstance().SetEventRule( EntityKind::PLAYER, EntityKind::SPIKE_HIT, GameEventType::SPIKE_HIT);
}

void SpikeDrop::SetContactEventCallback(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::SPIKE_HIT, [this](const ContactRule& rule)
		{
			auto entityKindA = rule.contactEvent_.entityA.entityKind_;
			auto entityKindB = rule.contactEvent_.entityB.entityKind_;
			auto idA = rule.contactEvent_.entityA.entityID_;
			auto idB = rule.contactEvent_.entityB.entityID_;
			auto actorA = actorMng_->FindActorByID(idA);
			auto actorB = actorMng_->FindActorByID(idB);
			SpikeDropPlayer* player = nullptr;
			Spike* spike = nullptr;
			if (entityKindA == EntityKind::PLAYER) { player = dynamic_cast<SpikeDropPlayer*>(actorA); spike = dynamic_cast<Spike*>(actorB); }
			if(entityKindB==EntityKind::PLAYER){player= dynamic_cast<SpikeDropPlayer*>(actorB); spike = dynamic_cast<Spike*>(actorA);}
			if (!player || !spike)return;
			//player->ChangeState<SpikeDropPlayerHit>();
		});
}

void SpikeDrop::SetEventCallBack(void)
{
	EventManager::GetInstance().SetContactEventCallback(GameEventType::CREATE_SPIKE, [this]()
		{
 			auto dropper = actorMng_->FindActorsByKind(EntityKind::DROPPER).back();
			auto dPos = dropper->GetTransform().pos;
			auto spike = std::make_unique<Spike>();
			spike->Load();
			spike->Init();
			spike->GetTransform().pos = dPos;
			spike->GetTransform().pos.y += -30;
			actorMng_->AddActor(std::move(spike), this);
		});
}

void SpikeDrop::LoadUI(void)
{
}

void SpikeDrop::LoadSE(void)
{
}

void SpikeDrop::InitUI(void)
{
}

void SpikeDrop::InitSE(void)
{
}

void SpikeDrop::InitCamera(void)
{
}
