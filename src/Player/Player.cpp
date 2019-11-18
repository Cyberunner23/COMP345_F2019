#include "Player.h"
#include <vector>
#include <iostream>

Player::Player() : Player("", 0, 0, Cities::BLUE, Armies::BLUE) {}

Player::Player(std::string playerName, int playerAge, int playerCoins, Cities cityColor, Armies armyColor)
{
    _name = new std::string(playerName);
    _age = new int(playerAge);
    _coins = new int(playerCoins);
	_score = new int(0);
    _bidingFacility = new BidingFacility();
    _hand = new Hand();
    _ownedRegions = new std::vector<Vertex>();
    _numHandCities = new unsigned int(0);
    _numHandArmies = new unsigned int(0);
    _cityColor = new Cities(cityColor);
    _armyColor = new Armies(armyColor);
    _startingRegionID = new unsigned int(0);
}

Player Player::youngestPlayer(std::vector<Player>* players)
{
    Player youngestPlayer;
    int* youngestAge = players->at(0).getage();
    for (auto& player : *players) {
    	if (*player.getage() < *youngestAge) {
    		*youngestAge = *player.getage();
    		youngestPlayer = player;
    	}
    }

    return youngestPlayer;
}


Player Player::bidingWinner(std::vector<Player>* players)
{
	Player bidingWinner;
	std::vector<Player>* tiedPlayers = new std::vector<Player>(); //keep a list of players who tied their bid
	int* highestBid = findHighestBid(players);

	for (auto& player : *players) {
		if (*player.getBidingFacility()->bid == *highestBid)
			tiedPlayers->push_back(player);
	}

	//If more than 2 tiedPlayers than we check for youngest
	if (tiedPlayers->size() > 1)
		return bidingWinner = youngestPlayer(tiedPlayers);

	//highestBid = 0 means all players bid 0
	if (*highestBid == 0)
		return bidingWinner = youngestPlayer(players);

	return bidingWinner = tiedPlayers->at(0);
}

int* Player::findHighestBid(std::vector<Player>* players)
{
	Player bidingWinner;
	std::vector<Player>* tiedPlayers = new std::vector<Player>(); //keep a list of players who tied their bid
	int* highestBid = players->at(0).getBidingFacility()->bid;

	for (auto& player : *players) {
		if (*player.getBidingFacility()->bid > *highestBid)
			*highestBid = *player.getBidingFacility()->bid;
	}

	return highestBid;
}

void Player::revealBids(std::vector<Player>* players)
{
	for (auto& player : *players) {
		std::cout << *player.getName() << " has bid " << *player.getBidingFacility()->bid << " coins." << std::endl;
	}
}


int* Player::assignCoinsToPlayers(std::vector<Player>* players, int* coins)
{
	for (Player& player : *players) {
		player.setCoins(coins);
	}

	return coins;
}

//Assigns number of coins to each player depending on their number
int* Player::assignCoinsToPlayers(std::vector<Player>* players)
{
	switch (players->size()) {
	case 2:
		return assignCoinsToPlayers(players, new int(14));
	case 3:
		return assignCoinsToPlayers(players, new int(11));
	case 4:
		return assignCoinsToPlayers(players, new int(9));
	case 5:
		return assignCoinsToPlayers(players, new int(8));
	}
}

void Player::displayPlayers(std::vector<Player>* players)
{
	std::cout << "\n------- Displaying players information -------" << std::endl;
	for (auto& player : *players) {
		std::cout << "Name: " << *player.getName() << std::endl;
		std::cout << "Age: " <<  *player.getage() << std::endl;
		std::cout << "Coins: " << *player.getCoins() << std::endl;
		std::cout << "Cards in hand: " << player.getHand()->HandList->size() << " cards" << std::endl;
		std::cout << "Num of armies in hand: " << player.getNumHandArmies() << std::endl;
		std::cout << "Num of cities in hand: " << player.getNumHandCities() << std::endl;
		std::cout << "-----------------------------" << std::endl;
	}
}

//When Player wins a bid he has to pay coins and
void Player::PayCoin()
{
    /*_bidingFacility->supply += _bidingFacility->bid;
    _coins -= _bidingFacility->bid;*/
}

bool Player::executeStrategy(GameState state, int turn) {
    return this->_strategy->execute(state, turn);
}

void Player::changeStrategy()
{
	std::string changeStrategy;
	int chooseStrategy;
	std::cout << "Do you wanna change your strategy? (y/n): ";
	while (std::cin >> changeStrategy && (changeStrategy != "y" && changeStrategy != "n"))
		std::cout << "\nPlease select a valid choice (y/n): ";
	if (changeStrategy == "y") {
		std::cout << "Press one of the following to select your new strategy: \n1. Human Player\n2. Greedy Computer\n3. Moderate Computer\nEnter your choice: ";
		while (std::cin >> chooseStrategy && (chooseStrategy < 1 || chooseStrategy > 3))
			std::cout << "\nPlease select a valid option (1,2,3): ";
		switch (chooseStrategy)
		{
		case 1:
			this->setPlayerStrategies(new HumanPlayer());
			break;
		case 2:
			this->setPlayerStrategies(new GreedyComputer());
			break;
		case 3:
			this->setPlayerStrategies(new ModerateComputer());
			break;
		}
	}
	else
		std::cout << "You chose to not change your strategy.. " << std::endl;

}

bool Player::RunAction(Map* map, Deck* deck, Cards card)
{
	int choice;

	switch (card)
	{
	case f1: //Move 3 Armies
		return MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		break;
	case f2: //Add 3 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case f3: //Destroy 1 Army or Build City
		std::cout << "Do you wanna destroy 1 Army (press 1) or build a City (press 2): ";
		while (std::cin >> choice && (choice != 1 && choice != 2)) {
			std::cout << "\nPlease press 1 or 2 to choose your action: ";
		}
		if (choice == 1) {
			std::cout << "You chose to destroy an army.. " << std::endl;
			return DestroyArmy(map, deck);
		}
		else {
			std::cout << "You chose to build a city.. " << std::endl;
			return BuildCity(map);
		}
		break;
	case f4: //Add 2 Armies or Move 3 Armies
		std::cout << "Do you wanna add 2 Armies (press 1) or move 3 Armies (press 2): ";
		while (std::cin >> choice && (choice != 1 && choice != 2)) {
			std::cout << "\nPlease press 1 or 2 to choose your action: " << std::endl;
		}
		if (choice == 1) {
			std::cout << "You chose to add 2 Armies.. " << std::endl;
			return PlaceNewArmies(map) && PlaceNewArmies(map);
		}
		else {
			std::cout << "You chose to move 3 armies.. " << std::endl;
			return MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		}
		break;
	case f5: //Move 4 Armies via Ship
		return MoveOverLandOrWater(map) && MoveOverLandOrWater(map) && MoveOverLandOrWater(map) && MoveOverLandOrWater(map);
		break;
	case f6: //Build City
		return BuildCity(map);
		break;
	case f7: //Move 3 Armies via Ship
		return MoveOverLandOrWater(map) && MoveOverLandOrWater(map) && MoveOverLandOrWater(map);
		break;
	case f8: //Move 6 Armies
		return MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		break;
	case c1: //Build City
		return BuildCity(map);
		break;
	case c2: //Destroy 1 Army and Add 1 Army
		return DestroyArmy(map, deck) && PlaceNewArmies(map);
		break;
	case c3: //Add 3 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case c4: //Move 4 Armies
		return MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		break;
	case c5: //Move 5 Armies
		return MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		break;
	case c6: //Add 3 Armies (DOUBLE)
		return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case c7: //Move 3 Armies via Ship
		return (MoveOverLandOrWater(map) && MoveOverLandOrWater(map) && MoveOverLandOrWater(map));
		break;
	case c8: //Move 4 Armies
		return MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		break;
	case c9: //Build City
		return BuildCity(map);
		break;
	case c10: //Add 4 Armies or Move 2 Armies*
		std::cout << "Do you wanna add 4 Armies (press 1) or move 2 Armies (press 2): ";
		while (std::cin >> choice && (choice != 1 && choice != 2)) {
			std::cout << "\nPlease press 1 or 2 to choose your action: ";
		}
		if (choice == 1) {
			std::cout << "You chose to add 4 Armies.. " << std::endl;
			return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		}
		else {
			std::cout << "You chose to move 2 Armies.. " << std::endl;
			return MoveArmies(map) && MoveArmies(map);
		}
		break;
	case a1: //Move 4 Armies
		return MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		break;
	case a2: //Add 3 Armies or Move 4 Armies
		std::cout << "Do you wanna add 3 Armies (press 1) or move 4 Armies (press 2): ";
		while (std::cin >> choice && (choice != 1 && choice != 2)) {
			std::cout << "\nPlease press 1 or 2 to choose your action: ";
		}
		if (choice == 1) {
			std::cout << "You chose to add 3 Armies.. " << std::endl;
			return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		}
		else {
			std::cout << "You chose to move 4 Armies.. " << std::endl;
			return MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		}
		break;
	case a3: //Move 5 Armies
		return MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		break;
	case a4: //Add 3 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case a5: //Add 3 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case a6: //Move 3 Armies via Ship
		return MoveOverLandOrWater(map) && MoveOverLandOrWater(map) && MoveOverLandOrWater(map);
		break;
	case a7: //Build City
		return BuildCity(map);
		break;
	case a8: //Add 4 Armies or Move 3 Armies
		std::cout << "Do you wanna add 4 Armies (press 1) or move 3 Armies (press 2): ";
		while (std::cin >> choice && (choice != 1 && choice != 2)) {
			std::cout << "\nPlease press 1 or 2 to choose your action: ";
		}
		if (choice == 1) {
			std::cout << "You chose to add 4 Armies.. " << std::endl;
			return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		}
		else {
			std::cout << "You chose to move 3 Armies.. " << std::endl;
			return MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		}
		break;
	case a9: //Move 4 Armies (DOUBLE)
		return MoveArmies(map) && MoveArmies(map) && MoveArmies(map) && MoveArmies(map);
		break;
	case o1: //Move 2 Armies
		return MoveArmies(map) && MoveArmies(map);
		break;
	case o2: //Move 3 Armies via Ship
		return MoveOverLandOrWater(map) && MoveOverLandOrWater(map) && MoveOverLandOrWater(map);
		break;
	case o3: //Move 2 Armies via Ship
		return MoveOverLandOrWater(map) && MoveOverLandOrWater(map);
		break;
	case o4: //Add 3 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case o5: //Add 3 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case o6: //Add 2 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case o7: //Move 2 Armies via Ship
		return MoveOverLandOrWater(map) && MoveOverLandOrWater(map);
		break;
	case cr1: //Add 2 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case cr2: //Add 2 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	case cr3: //Move 2 Armies
		return MoveArmies(map) && MoveArmies(map);
		break;
	case cr4: //Add 1 Army
		return PlaceNewArmies(map);
		break;
	case cr5: //Add 2 Armies
		return PlaceNewArmies(map) && PlaceNewArmies(map);
		break;
	}
}

// Place 1 army
bool Player::PlaceNewArmies(Map* map)
{
	// Check if player has armies to place
	if (getNumHandArmies() == 0)
	{
		std::cout << "You cannot place any new armies! All of your armies are deployed!" << std::endl;
		return false;
	}

	bool armyPlaced = false;
	while (!armyPlaced)
	{
		unsigned int countryID = 0;
		if (!countryIDUserInput(map, countryID, "\"Please enter the Country ID"))
		{
			return false;
		}

		auto isStartingCountry = [this](unsigned int countryID) { return countryID == getStartingRegionID(); };
		auto playerHasCityInCountry = [this](CountryNode* node)
		{ return std::find(node->CitiesInCountry->begin(), node->CitiesInCountry->end(), getCityColor()) != node->CitiesInCountry->end(); };
		//auto playerAlreadyHasArmyInCountry = [this](CountryNode* node)
		//    { return std::find(node->ArmiesInCountry->begin(), node->ArmiesInCountry->end(), getArmyColor()) != node->ArmiesInCountry->end(); };

		CountryNode* node = map->findCountryByID(countryID);
		// Is starting region or contains city
		if ((isStartingCountry(countryID)
			|| playerHasCityInCountry(node))
			/*&& !playerAlreadyHasArmyInCountry(node)*/)
		{
			// decrement num armies in hand
			int numArmies = getNumHandArmies();
			numArmies--;
			setNumHandArmies(numArmies);
			// Add army to country node
			node->ArmiesInCountry->push_back(getArmyColor());

			armyPlaced = true;
		}
		else
		{
			std::cout << "You cant place an army here..." << std::endl;
		}
	}

	return true;
}

bool Player::MoveArmies(Map* map, bool canMoveOverWater)
{

	bool armyMoved = false;
	while (!armyMoved)
	{

		unsigned int countryIDSrc = 0;
		unsigned int countryIDDest = 0;

		std::cout << "Moving an army" << std::endl;
		if (!countryIDUserInput(map, countryIDSrc, "Input the starting country ID"))
		{
			return false;
		}

		if (!countryIDUserInput(map, countryIDDest, "Input the destination country ID"))
		{
			return false;
		}

		if ((canMoveOverWater && map->areCountriesConnectedByWater(countryIDSrc, countryIDDest)) || map->areCountriesConnected(countryIDSrc, countryIDDest))
		{
			// Can do move

			CountryNode* srcCountry = map->findCountryByID(countryIDSrc);
			CountryNode* destCountry = map->findCountryByID(countryIDDest);

			auto it = std::find(srcCountry->ArmiesInCountry->begin(), srcCountry->ArmiesInCountry->end(), getArmyColor());
			if (it == srcCountry->ArmiesInCountry->end())
			{
				std::cout << "You dont have an army in the starting country..." << std::endl;
				continue;
			}

			srcCountry->ArmiesInCountry->erase(it);
			destCountry->ArmiesInCountry->push_back(getArmyColor());

			armyMoved = true;
		}
		else
		{
			// Cant do move
			std::cout << "These 2 countries aren't connected" << std::endl;
		}
	}

	return true;
}

bool Player::countryIDUserInput(Map* map, unsigned int& countryID, std::string queryText)
{
	bool inputTaken = false;

	do
	{
		std::string input;
		std::cout << queryText << " (q/Q to cancel): ";
		std::cin >> input;

		if (input == "q" || input == "Q")
		{
			std::cout << "Input canceled" << std::endl;
			return false;
		}

		try
		{
			countryID = (unsigned int)std::stoi(input);
		}
		catch (std::exception & e)
		{
			std::cout << "ID must be a number..." << std::endl;
			continue;
		}

		if (countryID > map->getNumCountries())
		{
			std::cout << "invalid ID range..." << std::endl;
			continue;
		}

		inputTaken = true;
	} while (!inputTaken);

	return true;
}

// Does 1 army, 1 move, card logic will handle the 3 moves
bool Player::MoveArmies(Map* map)
{
	return MoveArmies(map, false);
}

// Does 1 army, 1 move, card logic will handle the 3 moves
bool Player::MoveOverLandOrWater(Map* map)
{
	return MoveArmies(map, true);
}

bool Player::BuildCity(Map* map)
{
	// Check if player has cities to place
	if (getNumHandCities() == 0)
	{
		std::cout << "You cannot place any new cities! All of your cities are placed!" << std::endl;
		return false;
	}

	bool cityPlaced = false;
	while (!cityPlaced)
	{
		unsigned int countryID = 0;
		if (!countryIDUserInput(map, countryID, "\"Please enter the Country ID"))
		{
			return false;
		}

		auto playerHasArmyInCountry = [this](CountryNode* node)
		{ return std::find(node->ArmiesInCountry->begin(), node->ArmiesInCountry->end(), getArmyColor()) != node->ArmiesInCountry->end(); };

		CountryNode* node = map->findCountryByID(countryID);
		// Is starting region or contains city
		if (playerHasArmyInCountry(node))
		{
			// decrement num cities in hand
			int numCities = getNumHandCities();
			numCities--;
			setNumHandCities(numCities);

			// Add city to country node
			node->CitiesInCountry->push_back(getCityColor());

			cityPlaced = true;
		}
		else
		{
			std::cout << "You cant place a city here..." << std::endl;
		}
	}

	return true;
}

bool Player::DestroyArmy(Map* map, Deck* deck)
{
	bool armyDestroyed = false;
	while (!armyDestroyed)
	{
		unsigned int countryID = 0;
		if (!countryIDUserInput(map, countryID, "Please enter the Country ID"))
		{
			return false;
		}

		CountryNode* node = map->findCountryByID(countryID);
		Armies armyToDestroy;
		if (!node->canDestroyArmy(getArmyColor()))
		{
			std::cout << "There are no armies to be destroyed in this country." << std::endl;
		}
		else
		{
			bool armyChosen = false;
			do
			{
				std::string input;
				std::cout << "Enter the army color to destroy (q/Q to cancel): " << std::endl;
				std::cin >> input;

				if (input == "q" || input == "Q")
				{
					std::cout << "Destroy Army canceled" << std::endl;
					return false;
				}

				if (findByValue(armyToDestroy, *deck->ArmiesMap, input))
				{
					armyChosen = true;
				}
				else
				{
					std::cout << "Army not found..." << std::endl;
					continue;
				}

			} while (!armyChosen);
		}

		node->destroyArmy(armyToDestroy);
		armyDestroyed = true;
	}

	return true;
}

bool Player::AndOrAction()
{
	return true;
}

bool Player::Ignore()
{
	std::cout << "Card ignored" << std::endl;
	return true;
}

void Update()
{
  DisplayPlayer();
}
void DisplayPlayer(GameState gs, int cardCost)
{
  std::cout<< "Name: " << this.getName(); << std::endl;
  std::cout <<"They've chosen " << gs.GameDeck->DeckMap->at(*(this.getHand()->end() - 1)) << std::endl;
  std::cout <<"It costs:  " << cardCost << std::endl;
}
