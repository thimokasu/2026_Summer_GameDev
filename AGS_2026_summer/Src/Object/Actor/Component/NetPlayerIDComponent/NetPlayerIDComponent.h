#pragma once
#include "../ComponentBase.h"
#include"../../../../Net/NetStructures.h"
class NetPlayerIDComponent :
    public ComponentBase
{
public:
	NetPlayerIDComponent();
	~NetPlayerIDComponent(void) = default;
	//ユーザID
	void SetUserId(int id) { userId_ = id; }
	int GetUserId(void) const { return userId_; }

	//プレイヤータグ
	void SetPlayerTag(const PLAYERS tag) { playerTag_ = tag; }
	PLAYERS GetPlayerTag(void) const { return playerTag_; }
private:
	int userId_ = -1; //ユーザID
	PLAYERS playerTag_ = PLAYERS::PLAYER_1; //プレイヤータグ
};

