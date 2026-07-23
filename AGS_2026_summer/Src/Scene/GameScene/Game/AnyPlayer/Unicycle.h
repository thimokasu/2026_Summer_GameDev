#pragma once
#include"../GameBase.h"
class GameMessageUI;
class Distance;
class MessageImageUI;

using SetUI = std::function<void(std::uint32_t)>;


class Unicycle :public GameBase
{
public:
	Unicycle(ActorManager* actMng, CollisionManager* colMng);
	~Unicycle(void);

	void SubLoad(void)override;
	void SubInit(void)override;
	void SubUpdate(void)override;
	void SubDraw(void)override;
	void SubRelease(void)override;

	void SetContactEventRule(void)override;
	void SetContactEventCallback(void)override;
	void SetEventCallBack(void)override;

	void LoadUI(void)override;
	void LoadSE(void)override;
	void InitUI(void)override;
	void InitSE(void)override;
	void InitCamera(void)override;
private:
	std::shared_ptr<GameMessageUI> msgUI_;
	std::shared_ptr<Distance> distanceUI_;
	std::shared_ptr<MessageImageUI> ImageUI_;
	SetUI setUI_;

	int finishCount_ = 0;

};

