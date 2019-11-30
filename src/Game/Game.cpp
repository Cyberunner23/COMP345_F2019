#include "Game.h"
#include "Game.h"
#include "Game.h"
#include "Game.h"

std::string Game::selectMap()
{
	int mapSelection;
	std::string mapPath;

	std::cout << "Which map do you want to use: 1, 2, 3 (invalid) or 4 (invalid): ";
	while (std::cin >> mapSelection && (mapSelection < 1 || mapSelection > 2)) {
		std::cout << "\nYou cannot choose an invalid map!!";
		std::cout << "\nPlease enter a valid map: ";
	}

	switch (mapSelection)
	{
	case 1:
		return mapPath = "data/map1.map";
	case 2:
		return mapPath = "data/map2.map";
	case 3:
		return mapPath = "data/map_invalid1.map";
	case 4:
		return mapPath = "data/map_invalid2.map";
	default:
		std::cout << "Invalid selection, defaulting to map 1" << std::endl;
		return mapPath = "data/map1.map";
		
	}
}

std::vector<Player>* Game::createPlayers(GameState* state)
{
	int playerNum;
	std::vector<Player>* players = new std::vector<Player>();

	std::cout << "How many players? ";
	while (std::cin >> playerNum && (playerNum < 2 || playerNum > 4)) {
		if (playerNum > 4)
			std::cout << "\nYou cannot play with more than 4 players.";
		else
			std::cout << "\nYou cannot play with less than 2 players.";

		std::cout << "\nPlease enter a valid number of players: ";
	}

	//Creating the players
	for (int i = 0; i < playerNum; i++)
	{
		Player p(state);

		std::string* name = new std::string("Player " + std::to_string(i + 1));
		//int* age = new int();
		//std::cout << "Please enter age for " << *name << ": ";
		//while (std::cin >> *age && (*age < 0)) {
		//	std::cout << "\nPlease enter a valid age: ";
		//}

		p.setName(name);
		p.setage(new int(25));
		p.setStartingRegionID(Map::GetInstance().getStartingCountryID());
		selectStrategy(&p);

		std::cout << "Adding " << *p.getName() << std::endl;
		players->push_back(p);
	}

	return players;
}

void Game::displayFaceUpCards(GameState state)
{
	int position = 1;
	std::cout << "\n------- Displaying Cards -------" << std::endl;
	for (auto& card : *state.ShownCards) {
		std::cout << "Position: " << position << ", Action: " << state.GameDeck->DeckMap->at(card) << std::endl;
		position++;
	}
}

void Game::displayGameState(GameState state)
{
	std::cout << "\n------- Displaying Game information -------" << std::endl;
	std::cout << "Players: " << state.Players->size() << std::endl;
	std::cout << "Deck: " << state.GameDeck->CardList->size() << " cards" << std::endl;
	std::cout << "supply: " << *state.supply << " coins" << std::endl;
	std::cout << "-----------------------------" << std::endl;
}

void Game::selectStrategy(Player* p)
{
	int chooseStrategy;
	std::cout << "Please enter strategy for " << *p->getName() << ": " << std::endl;
	std::cout << "Press one of the following to select a strategy: \n1. Human Player\n2. Greedy Computer\n3. Moderate Computer\n4. Random Computer\nEnter your choice: ";
	
	while (std::cin >> chooseStrategy && (chooseStrategy < 1 || chooseStrategy > 4))
		std::cout << "\nPlease select a valid option (1,2,3,4): ";

	switch (chooseStrategy)
	{
	case 1:
		p->setPlayerStrategies(new HumanPlayer());
		break;
	case 2:
		p->setPlayerStrategies(new GreedyComputer());
		break;
	case 3:
		p->setPlayerStrategies(new ModerateComputer());
		break;
	case 4:
		p->setPlayerStrategies(new RandomComputer());
		break;
	}
}


bool Game::isArmyAndCityColorAvailable(GameState* state, Armies armyColor, Cities cityColor)
{
	for (auto p : *state->Players)
		if (p.getArmyColor() == armyColor && p.getCityColor() == cityColor)
			return false;

	return true;
}

Armies Game::getArmyColorWithUserInput(int colorChoosen)
{

	switch (colorChoosen)
	{
	case 1:
		return Armies::RED;
		break;
	case 2:
		return Armies::WHITE;
		break;
	case 3:
		return Armies::BLUE;
		break;
	case 4:
		return Armies::YELLOW;
		break;
	case 5:
		return Armies::GREEN;
		break;
	}
}

Cities Game::getCityColorWithUserInput(int colorChoosen)
{

	switch (colorChoosen)
	{
	case 1:
		return Cities::RED;
		break;
	case 2:
		return Cities::WHITE;
		break;
	case 3:
		return Cities::BLUE;
		break;
	case 4:
		return Cities::YELLOW;
		break;
	case 5:
		return Cities::GREEN;
		break;
	}
}

void Game::chooseArmiesAndCitiesColor(GameState* state)
{
	int chooseColor;

	for (auto p : *state->Players) {
		std::cout << "Please enter army/city color for " << *p.getName() << ": " << std::endl;
		std::cout << "Press one of the following to select an army/city color: \n1. Red\n2. White\n3. Blue(invalid)\n4. Yellow\n5. Green\nEnter your choice: ";

		while (std::cin >> chooseColor && (chooseColor < 1 || chooseColor > 5 || (state->Players->size() == 2 && chooseColor == 2) 
			|| !isArmyAndCityColorAvailable(state, getArmyColorWithUserInput(chooseColor), getCityColorWithUserInput(chooseColor)))) {
			if(chooseColor < 1 || chooseColor > 5)
				std::cout << "\nPlease select a valid option (1,2,3,4,5): ";
			else if (state->Players->size() == 2 && chooseColor == 2) {
				std::cout << "\nThis is the third non player army/city color!!!";
				std::cout << "\nPlease select another color: ";
				continue;
			}
			else if (!isArmyAndCityColorAvailable(state, getArmyColorWithUserInput(chooseColor), getCityColorWithUserInput(chooseColor))) {
				std::cout << "\nColor '" << state->GameDeck->ArmiesMap->at(getArmyColorWithUserInput(chooseColor)) << "' has already been choosen!!" << std::endl;
				std::cout << "Please select another color: ";
				continue;
			}
		}

		Armies armyColor = getArmyColorWithUserInput(chooseColor);
		Cities cityColor = getCityColorWithUserInput(chooseColor);

		p.setCityColor(cityColor);
		p.setArmyColor(armyColor);
		p.setNumHandArmies(14);
		p.setNumHandCities(3);

		std::cout << *p.getName() << " has choosen the '" << state->GameDeck->ArmiesMap->at(armyColor) << "' set of color for cities/armies" << std::endl;

	}
}

void Game::PlaceArmiesInCountryStartup(GameState& state)
{
    unsigned int startingCountryID = Map::GetInstance().getStartingCountryID();
    CountryNode* startingCountry = Map::GetInstance().findCountryByID(startingCountryID);

    if (state.Players->size() == 2)
    {
		int countryID;
		PlaceArmiesInCountryStartup(state, startingCountry);
		Armies newArmy = Armies::WHITE; //thrid non player army
		for (int i = 0; i < 10; i++) { //Place 10 armies on the map
			Player player = state.Players->at(i%2);
			std::cout << *player.getName() << ", please enter the country ID where you wanna place the army: ";
			while (std::cin >> countryID && (countryID < 1 || countryID > Map::GetInstance().getNumCountries())) {
				std::cout << "Invalid ID range ..." << std::endl;
				std::cout << "Please enter a valid country ID: ";
			}
			CountryNode* country = Map::GetInstance().findCountryByID(countryID);
			country->ArmiesInCountry->push_back(newArmy);
			std::cout << "\n" << *player.getName() << " just placed a new army." << std::endl;
		}
    }
	//More than 3 players
    else
    {
		PlaceArmiesInCountryStartup(state, startingCountry);
    }
}

void Game::PlaceArmiesInCountryStartup(GameState& state, CountryNode* startingCountry)
{
	//Each player placing 3 armies on starting region
	for (auto& player : *state.Players)
	{
		unsigned int numArmies = player.getNumHandArmies();
		numArmies -= 3;
		player.setNumHandArmies(numArmies);

		startingCountry->ArmiesInCountry->push_back(player.getArmyColor());
		startingCountry->ArmiesInCountry->push_back(player.getArmyColor());
		startingCountry->ArmiesInCountry->push_back(player.getArmyColor());

		std::cout << *player.getName() << " has finished placing his 3 armies on the starting region." << std::endl;
	}

	std::cout << "The starting region now contains " << startingCountry->ArmiesInCountry->size() << " armies." << std::endl;
}

void Game::tournamentResults(GameState* state) {
	ScoreCalculator* s = new ScoreCalculator(state);
	Player winningPlayer = s->CalculateScores();

	std::cout << "\n------- Displaying Tournament results -------";
	std::cout << "\n";
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "| Player # | Cards | Victory Points | Coins |" << std::endl;;

	for (auto player : *state->Players) {
		std::cout << "---------------------------------------------" << std::endl;;
		std::cout << "| " << *player.getName() << " |   " << player.getHand()->HandList->size() << (player.getHand()->HandList->size() < 10? "   |       " : "  |       ") << *player.getScore() << (*player.getScore() < 10? "        |   " : "       |   ") << *player.getCoins() << "   |" << std::endl;;
	}
	std::cout << "---------------------------------------------" << std::endl;;

	std::cout << "\nCongratulations " << *winningPlayer.getName() << "!! You have won this tournament!!!" << std::endl;

}
