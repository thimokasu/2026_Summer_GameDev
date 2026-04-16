#pragma once
#include"ContactSystem.h"
#include"ContactRuleTable.h"

#include<vector>
#include<unordered_map>
class GameContactSystem
{
public:
	GameContactSystem();
	~GameContactSystem();

	void Update(std::vector<ContactRule>contactRule);

	void Clear(void);

private:
	// ÚGƒCƒxƒ“ƒg‚Ìˆ—
	void Procese(ContactRule rule);

	ContactSystem contactSystem_;
	ContactRuleTable contactRuleTable_;

	
};

