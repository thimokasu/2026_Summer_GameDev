#pragma once
#include"ContactSystem.h"
#include"ContactRuleTable.h"

#include<vector>
#include<unordered_map>
class ActorBase;


class GameContactSystem
{
public:
	GameContactSystem();
	~GameContactSystem();

	void Update(std::vector<ContactRule>contactRule, const std::vector<std::shared_ptr<ActorBase>>& objects);

	void Clear(void);

private:
	// ÚGƒCƒxƒ“ƒg‚Ìˆ—
	void Procese(ContactRule rule, const std::vector<std::shared_ptr<ActorBase>>& objects);

	void SetColor(const std::vector<std::shared_ptr<ActorBase>>& objects);

	ContactSystem contactSystem_;
	ContactRuleTable contactRuleTable_;

	
};

