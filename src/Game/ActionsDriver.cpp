
#include "Game/GameState.hpp"
#include "Map/MapLoader.h"

int main(int argc, char** argv)
{

    GameState state;

    // Load Map
    std::string mapPath = "data/map1.map";
    MapLoader loader;

    if (!loader.loadMap(mapPath))
    {
        std::cout << "Failed to open map!" << std::endl;
        return 1;
    }

    // Create Deck
    state.GameDeck = new Deck();
	state.GameDeck->shuffleDeck();

    // Create players
    state.Players = new std::vector<Player>();
    std::string* nameP1 = new std::string("Player 1");
    std::string* nameP2 = new std::string("Player 2");
    std::string* nameP3 = new std::string("Player 3");

    int* ageP1 = new int(23);
    int* ageP2 = new int(21);
    int* ageP3 = new int(22);

    Player p1;
    p1.setStartingRegionID(Map::GetInstance().getStartingCountryID());
    p1.setName(nameP1);
    p1.setage(ageP1);
    p1.setCityColor(Cities::BLUE);
    p1.setArmyColor(Armies::BLUE);
    p1.setNumHandArmies(14);
    p1.setNumHandCities(3);
    state.Players->push_back(p1);

    Player p2;
    p2.setStartingRegionID(Map::GetInstance().getStartingCountryID());
    p2.setName(nameP2);
    p2.setage(ageP2);
    p2.setCityColor(Cities::GREEN);
    p2.setArmyColor(Armies::GREEN);
    p2.setNumHandArmies(14);
    p2.setNumHandCities(3);
    state.Players->push_back(p2);

    Player p3;
    p3.setStartingRegionID(Map::GetInstance().getStartingCountryID());
    p3.setName(nameP3);
    p3.setage(ageP3);
    p3.setCityColor(Cities::RED);
    p3.setArmyColor(Armies::RED);
    p3.setNumHandArmies(14);
    p3.setNumHandCities(3);
    state.Players->push_back(p3);

    //Give cards to players
    for (auto& player : *state.Players) {
        //Each player should have 6 cards in hand after this
        for (int i = 0; i < 6; i++) {
            Card c = state.GameDeck->draw();
            player.getHand()->HandList->push_back(c);
        }
    }

    //Loop through players, make a player do the action for the card
    for (auto& player : *state.Players) {
        int i = 0;
        for (int j = 0; j < 2; j++) {
            Card c = player.getHand()->HandList->at(j);
            std::cout << *player.getName() << " is playing: '" << state.GameDeck->DeckMap->at(c.GetRawCard()) << "' from his hand." <<std::endl;
			bool actionRun = player.RunAction(&Map::GetInstance(), &state, c);
			std::cout << "Did action run? " << actionRun << std::endl;
			player.getHand()->HandList->erase(player.getHand()->HandList->begin() + j);
        }
        i++;
    }

	Player::displayPlayers(&state);

    return 0;
}