#include <vector>

#include "Map/MapLoader.h"
#include "Game/GameState.hpp"
#include "Deck/Deck.h"
#include "Player/BidingFacility.h"
#include "Game/Game.h"

int main(int argc, char** argv)
{

	GameState state;
	GameState state2;

	// Load Map
	std::string mapPath = "data/map1.map";
	MapLoader loader;
	Map* map = loader.loadMap(mapPath);

	if (map == nullptr)
	{
		std::cout << "Failed to open map!" << std::endl;
		return 1;
	}

	state.GameMap = map;
	state2.GameMap = map;

	// Create Deck
	state.GameDeck = new Deck();

	//Shuffling deck and drawing 6 cards
	state.GameDeck->shuffleDeck();
	state.ShownCards = new std::vector<Cards>();
	for (int i = 0; i < 6; i++) {
		Cards c = state.GameDeck->draw();
		std::cout << "You Have Drawn: " << state.GameDeck->DeckMap->at(c) << std::endl;
		state.ShownCards->push_back(c);
	}

	
	//Initialize Players 
	state.Players = new std::vector<Player>();
	state2.Players = new std::vector<Player>();

	std::string* nameP1 = new std::string("Player 1");
	std::string* nameP2 = new std::string("Player 2");
	std::string* nameP3 = new std::string("Player 3");

	int* ageP1 = new int(20);
	int* ageP2 = new int(30);
	int* ageP3 = new int(40);

	Player p1;
	p1.setName(nameP1);
	p1.setage(ageP1);
	p1.setCityColor(Cities::BLUE);
	p1.setArmyColor(Armies::BLUE);
	p1.setNumHandArmies(14);
	p1.setNumHandCities(3);
	state.Players->push_back(p1);
	state2.Players->push_back(p1);

	Player p2;
	p2.setName(nameP2);
	p2.setage(ageP2);
	p2.setCityColor(Cities::GREEN);
	p2.setArmyColor(Armies::GREEN);
	p2.setNumHandArmies(14);
	p2.setNumHandCities(3);
	state.Players->push_back(p2);
	state2.Players->push_back(p2);

	Player p3;
	p3.setName(nameP3);
	p3.setage(ageP3);
	p3.setCityColor(Cities::RED);
	p3.setArmyColor(Armies::RED);
	p3.setNumHandArmies(14);
	p3.setNumHandCities(3);
	state.Players->push_back(p3);

	//Each player places 3 armies on the starting region on the board. If playing with 2 players, each player
	//takes turns placing one army at a time of a third, non - player color in any region on the
	//board until ten armies have been placed.
	//Game::PlaceArmiesInCountryStartup(state);
	Game::PlaceArmiesInCountryStartup(state2);

	//Assign coins to each players
	int* maxCoins = Player::assignCoinsToPlayers(state2.Players);

	for (auto& player : *state2.Players) {
		player.getBidingFacility()->startBiding(maxCoins);
	}

	Player::revealBids(state2.Players);

	//Dertermining who won the bid
	Player bidingWinner;
	bidingWinner = Player::bidingWinner(state2.Players);
	std::cout << "\n" << *bidingWinner.getName() << " has won the bid. " << *bidingWinner.getBidingFacility()->bid << " coins are now going to the supply.";
	
	//Computing remaining coins of winner
	int* remainingCoins = new int(); 
	*remainingCoins = *bidingWinner.getCoins() - *bidingWinner.getBidingFacility()->bid;
	bidingWinner.setCoins(remainingCoins);
	std::cout << "\n" << *bidingWinner.getName() << " has now " << *bidingWinner.getCoins() << " coins.";

	//Putting the coins in supply
	state2.supply = new int();
	*state2.supply += *bidingWinner.getBidingFacility()->bid;
	std::cout << "\nThe supply contains now: " << *state2.supply << " coins." << std::endl;

	//Retrieve winning player in state.Players to determine who will be the next to play 
	int playerIndex = 0;
	for (Player& player : *state2.Players) {
		if (*bidingWinner.getName() == *player.getName()) {
			break;
		}
		playerIndex++;
	}
	state2.Players->at(playerIndex) = bidingWinner; 
	std::cout << "The next player to play will be: " << *state2.Players->at(++playerIndex%3).getName() << std::endl;

	Player::displayPlayers(state2.Players);

	delete map;
	delete maxCoins;
	delete remainingCoins;

	return 0;
}