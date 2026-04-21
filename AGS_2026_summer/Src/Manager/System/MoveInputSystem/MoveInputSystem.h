#pragma once
#include<vector>
#include<memory>
#include "../../../Net/NetStructures.h"
class ActorBase;

class MoveInputSystem
{
public:
	MoveInputSystem();
	~MoveInputSystem();

	void Load(std::map<int, NET_JOIN_USER> data);

	void Update(const std::vector<std::shared_ptr<ActorBase>>& objects);
	void testUpdate(const std::vector<std::shared_ptr<ActorBase>>& objects);

private:

	int key_;
	PLAYERS type_;
};

