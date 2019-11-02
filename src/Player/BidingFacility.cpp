#include "BidingFacility.h"
#include <iostream>

BidingFacility::BidingFacility() {
	bid = new int();
}

int BidingFacility::supply = 0; //Initialize static variable

void BidingFacility::startBiding(int* maxBid)
{
	int* playerBid = new int();
	std::cout << "Please enter your bid: ";
	while (std::cin >> *playerBid && (*playerBid < 0 || *playerBid > *maxBid)) {
		if (*playerBid > *maxBid)
			std::cout << "\nYou cannot bid more than what you have! The maximum you can bid is " << *maxBid << " coins.";
		else
			std::cout << "\nYou have entered an invalid number of coins.";

		std::cout << "\nPlease enter a valid number of coins to bid: ";
	}

	*bid = *playerBid;
}
