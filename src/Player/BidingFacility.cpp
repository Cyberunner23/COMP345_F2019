#include "BidingFacility.h"
#include <iostream>

BidingFacility::BidingFacility() {
	bid = 0;
}

int BidingFacility::supply = 0; //Initialize static variable

void BidingFacility::startBiding(int maxBid)
{
	int playerBid;
	std::cout << "Please enter your bid: ";
	while (std::cin >> playerBid && (playerBid < 0 || playerBid > maxBid)) {
		if (playerBid > maxBid)
			std::cout << "\nYou cannot bid more than what you have! The maximum you can bid is " << maxBid << " _coins.";
		else
			std::cout << "\nYou have entered an invalid number of _coins.";

		std::cout << "\nPlease enter a valid number of _coins to bid: ";
	}

	bid = playerBid;
}
