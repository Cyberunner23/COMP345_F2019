
#include "Player/BidingFacility.h"
#include "Player/Player.h"
#include <vector>
#include <iostream>


int main(int argc, char** argv)
{
	std::vector<Player*> playersList;
	int maxCoins = 11;

	//Creating Player objects and enabling them to start biding
	Player* p1 = new Player("William", 23, maxCoins, Cities::BLUE, Armies::BLUE);
	p1->getBidingFacility()->startBiding(maxCoins);
	playersList.push_back(p1);

	Player* p2 = new Player("Alex FL", 21, maxCoins, Cities::GREEN, Armies::GREEN);
	p2->getBidingFacility()->startBiding(maxCoins);
	playersList.push_back(p2);

	Player* p3 = new Player("Al->>x->Hayeur", 22, maxCoins, Cities::RED, Armies::RED);
	p3->getBidingFacility()->startBiding(maxCoins);
	playersList.push_back(p3);

	//Revealing each player's bid
	Player::revealBids(playersList);

	//Dertermining who won the bid
	Player* bidingWinner;
	bidingWinner = Player::bidingWinner(playersList);

	//Winner puts the _coins he bid in supply
	bidingWinner->PayCoin();

	std::cout << "\n" << *bidingWinner->getName() << " has won the bid. " << bidingWinner->getBidingFacility()->bid << " _coins are now going to the supply.";
	std::cout << "\nThe supply contains now: " << BidingFacility::supply << " _coins." << std::endl;


	//TEST 1: Player who bid the most _coins wins
	p1->getBidingFacility()->bid = 9; //William _age 23 (should win)
	p2->getBidingFacility()->bid = 5; //Alex FL _age 21
	p3->getBidingFacility()->bid = 0; //Alex Hayeur _age 22
	bidingWinner = Player::bidingWinner(playersList);
	std::cout << "TEST 1: Checking if player who bid the most _coins wins, should PASS, is " << (*bidingWinner->getName() == "William" ? "PASS" : "FAIL") << std::endl;

	//TEST 2: Youngest player wins the bid if there are ties 
	p1->getBidingFacility()->bid = 7; //William _age 23
	p2->getBidingFacility()->bid = 3; //Alex FL _age 21
	p3->getBidingFacility()->bid = 7; //Alex Hayeur _age 22 (should win)
	bidingWinner = Player::bidingWinner(playersList);
	std::cout << "TEST 2: Checking if Youngest player wins the bid if there are ties , should PASS, is " << (*bidingWinner->getName() == "Alex Hayeur" ? "PASS" : "FAIL") << std::endl;

	//TEST 3: Youngest player wins the bid if all bids are zero
	p1->getBidingFacility()->bid = 0; //William _age 23
	p2->getBidingFacility()->bid = 0; //Alex FL _age 21 (should win)
	p3->getBidingFacility()->bid = 0; //Alex Hayeur _age 22
	bidingWinner = Player::bidingWinner(playersList);
	std::cout << "TEST 3: Checking if Youngest player wins the bid if all bids are zero, should PASS, is " << (*bidingWinner->getName() == "Alex FL" ? "PASS" : "FAIL") << std::endl;

	return 0;
}
