
#include "Player/BidingFacility.h"
#include "Player/Player.h"
#include <vector>
#include <iostream>


int main(int argc, char** argv)
{
	std::vector<Player>* playersList = new std::vector<Player>();
	int* maxCoins =new int(11);

	//Creating Player objects and enabling them to start biding
	std::string* nameP1 = new std::string("Player 1");
	std::string* nameP2 = new std::string("Player 2");
	std::string* nameP3 = new std::string("Player 3");

	int* ageP1 = new int(23);
	int* ageP2 = new int(21);
	int* ageP3 = new int(22);

	Player p1;
	p1.setName(nameP1);
	p1.setage(ageP1);
	p1.setCityColor(Cities::BLUE);
	p1.setArmyColor(Armies::BLUE);
	playersList->push_back(p1);

	Player p2;
	p2.setName(nameP2);
	p2.setage(ageP2);
	p2.setCityColor(Cities::GREEN);
	p2.setArmyColor(Armies::GREEN);
	playersList->push_back(p2);

	Player p3;
	p3.setName(nameP3);
	p3.setage(ageP3);
	p3.setCityColor(Cities::RED);
	p3.setArmyColor(Armies::RED);
	playersList->push_back(p3);

	for (auto& player : *playersList) {
		player.getBidingFacility()->startBiding(maxCoins);
	}

	//Revealing each player's bid
	Player::revealBids(playersList);

	//Dertermining who won the bid
	Player bidingWinner;
	bidingWinner = Player::bidingWinner(playersList);

	//Winner puts the _coins he bid in supply
	//bidingWinner.PayCoin();

	std::cout << "\n" << *bidingWinner.getName() << " has won the bid. " << *bidingWinner.getBidingFacility()->bid << " coins are now going to the supply.";
	std::cout << "\nThe supply contains now: " << BidingFacility::supply << " coins." << std::endl;


	//TEST 1: Player who bid the most _coins wins
	p1.getBidingFacility()->bid = new int(9); //William age 23 (should win)
	p2.getBidingFacility()->bid = new int(5); //Alex FL age 21
	p3.getBidingFacility()->bid = new int(0); //Alex Hayeur age 22
	bidingWinner = Player::bidingWinner(playersList);
	std::cout << "TEST 1: Checking if player who bid the most coins wins, should PASS, is " << (*bidingWinner.getName() == *nameP1 ? "PASS" : "FAIL") << std::endl;

	//TEST 2: Youngest player wins the bid if there are ties 
	p1.getBidingFacility()->bid = new int(7); //William age 23
	p2.getBidingFacility()->bid = new int(3); //Alex FL age 21
	p3.getBidingFacility()->bid = new int(7); //Alex Hayeur age 22 (should win)
	bidingWinner = Player::bidingWinner(playersList);
	std::cout << "TEST 2: Checking if Youngest player wins the bid if there are ties , should PASS, is " << (*bidingWinner.getName() == *nameP3 ? "PASS" : "FAIL") << std::endl;

	//TEST 3: Youngest player wins the bid if all bids are zero
	p1.getBidingFacility()->bid = new int(0); //William age 23
	p2.getBidingFacility()->bid = new int(0); //Alex FL age 21 (should win)
	p3.getBidingFacility()->bid = new int(0); //Alex Hayeur age 22
	bidingWinner = Player::bidingWinner(playersList);
	std::cout << "TEST 3: Checking if Youngest player wins the bid if all bids are zero, should PASS, is " << (*bidingWinner.getName() == *nameP2 ? "PASS" : "FAIL") << std::endl;


	delete nameP1;
	delete nameP2;
	delete nameP3;
	delete ageP1;
	delete ageP2;
	delete ageP3;
	delete playersList;
	delete maxCoins;

	return 0;
}
