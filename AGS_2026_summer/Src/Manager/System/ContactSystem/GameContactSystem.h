#pragma once
#include"ContactSystem.h"
#include"ContactRuleTable.h"

#include<vector>
#include<unordered_map>
#include <functional>
class ActorBase;

using EventCallback = std::function<void(std::uint32_t)>;

class GameContactSystem
{
public:
	GameContactSystem();
	~GameContactSystem();

	void Update(std::vector<ContactRule>contactRule);

	void Clear(void);

	//イベントコールバックの設定
	void SetEventCallback(EventCallback callback)
	{
		eventCallback_ = callback;
	}

private:
	// 接触イベントの処理
	void Procese(ContactRule rule);
	

	ContactSystem contactSystem_;
	ContactRuleTable contactRuleTable_;
	EventCallback eventCallback_;

	
};


