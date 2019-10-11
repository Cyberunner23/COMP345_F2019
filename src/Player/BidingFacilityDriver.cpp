
#include "Player/BidingFacility.h"
#include "Player/Player.h"
#include <vector>
#include <iostream>


int main(int argc, char** argv)
{
	std::vector<Player*> playersList;
	int maxCoins = 11;

	//Creating Player objects and enabling them to start biding
	Player* p1 = new Player("William", 23, maxCoins);
	p1->bidingFacility->startBiding(maxCoins);
	playersList.push_back(p1);

	Player* p2 = new Player("Alex FL", 21, maxCoins);
	p2->bidingFacility->startBiding(maxCoins);
	playersList.push_back(p2);

	Player* p3 = new Player("Alex Hayeur", 22, maxCoins);
	p3->bidingFacility->startBiding(maxCoins);
	playersList.push_back(p3);

	//Revealing each player's bid
	Player::revealBids(playersList);

	//Dertermining who won the bid
	Player* bidingWinner;
	bidingWinner = Player::bidingWinner(playersList);

	//Winner puts the coins he bid in supply
	bidingWinner->PayCoin();

	std::cout << "\n" << bidingWinner->name << " has won the bid. " << bidingWinner->bidingFacility->bid << " coins are now going to the supply.";
	std::cout << "\nThe supply contains now: " << BidingFacility::supply << " coins." << std::endl;


	//TEST 1: Player who bid the most coins wins
	p1->bidingFacility->bid = 9; //William age 23 (should win)
	p2->bidingFacility->bid = 5; //Alex FL age 21 
	p3->bidingFacility->bid = 0; //Alex Hayeur age 22
	bidingWinner = Player::bidingWinner(playersList);
	std::cout << "TEST 1: Checking if player who bid the most coins wins, should PASS, is " << (bidingWinner->name == "William" ? "PASS" : "FAIL") << std::endl;

	//TEST 2: Youngest player wins the bid if there are ties 
	p1->bidingFacility->bid = 7; //William age 23
	p2->bidingFacility->bid = 3; //Alex FL age 21
	p3->bidingFacility->bid = 7; //Alex Hayeur age 22 (should win)
	bidingWinner = Player::bidingWinner(playersList);
	std::cout << "TEST 2: Checking if Youngest player wins the bid if there are ties , should PASS, is " << (bidingWinner->name == "Alex Hayeur" ? "PASS" : "FAIL") << std::endl;

	//TEST 3: Youngest player wins the bid if all bids are zero
	p1->bidingFacility->bid = 0; //William age 23
	p2->bidingFacility->bid = 0; //Alex FL age 21 (should win)
	p3->bidingFacility->bid = 0; //Alex Hayeur age 22 
	bidingWinner = Player::bidingWinner(playersList);
	std::cout << "TEST 3: Checking if Youngest player wins the bid if all bids are zero, should PASS, is " << (bidingWinner->name == "Alex FL" ? "PASS" : "FAIL") << std::endl;

	return 0;
}
