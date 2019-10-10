#pragma once

#include <vector>
#include <Player/Player.h>

class BidingFacility {

public:
	BidingFacility();
	int bid;
	int supply = 0;
	void startBiding(int bid);
	void winningPlayer(std::vector<Player> players);

};