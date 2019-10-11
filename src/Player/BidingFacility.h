#pragma once

#include <vector>

class BidingFacility {

public:
	BidingFacility();
	int bid;
	static int supply;
	void startBiding(int maxBid);
};