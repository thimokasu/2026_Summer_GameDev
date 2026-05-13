#pragma once
#include"../../../../Net/NetStructures.h"
struct NetPlayerID
{
	void SetUserID(int id) { userID = id; }
	int GetUserID() const { return userID; }
	void SetPlayerTag(PLAYERS tag) { playerTag_ = tag; }
	PLAYERS GetPlayerTag() const { return playerTag_; }
	int userID;
	PLAYERS playerTag_ = PLAYERS::PLAYER_1;
};