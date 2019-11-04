#include "Actions.hpp"

Actions::Actions(GameState* state, Player* player)
{
    _state = state;
    _player = player;
}

bool Actions::RunAction(Cards card)
{
	int choice;

    switch (card)
    {
        case f1: //Move 3 Armies
			return MoveArmies();
            break;
        case f2: //Add 3 Armies
			return PlaceNewArmies();
            break;
        case f3: //Destroy 1 Army or Build City
			std::cout << "Do you wanna destroy 1 Army (press 1) or build a City (press 2): ";
			while (std::cin >> choice && (choice != 1 && choice != 2)) {
				std::cout << "\nPlease press 1 or 2 to choose your action: ";
			}
			if (choice == 1) {
				std::cout << "You chose to destroy an army.. " << std::endl;
				return DestroyArmy();
			}
			else {
				std::cout << "You chose to build a city.. " << std::endl;
				return BuildCity();
			}
            break;
        case f4: //Add 2 Armies or Move 3 Armies
			std::cout << "Do you wanna add 2 Armies (press 1) or move 3 Armies (press 2): ";
			while (std::cin >> choice && (choice != 1 && choice != 2)) {
				std::cout << "\nPlease press 1 or 2 to choose your action: " << std::endl;
			}
			if (choice == 1) {
				std::cout << "You chose to add 2 Armies.. " << std::endl;
				return PlaceNewArmies();
			}
			else {
				std::cout << "You chose to build a City.. " << std::endl;
				return MoveArmies();
			}
            break;
        case f5: //Move 4 Armies via Ship
			return MoveOverLandOrWater();
            break;
        case f6: //Build City
			return BuildCity();
            break;
        case f7: //Move 3 Armies via Ship
			return MoveOverLandOrWater();
            break;
        case f8: //Move 6 Armies
			return MoveArmies();
            break;
        case c1: //Build City
			return BuildCity();
            break;
        case c2: //Destroy 1 Army and Add 1 Army
			std::cout << "Do you wanna destroy 1 Army (press 1) or add 1 Army (press 2): ";
			while (std::cin >> choice && (choice != 1 && choice != 2)) {
				std::cout << "\nPlease press 1 or 2 to choose your action: ";
			}
			if (choice == 1) {
				std::cout << "You chose to destroy an Army.. " << std::endl;
				return DestroyArmy();
			}
			else {
				std::cout << "You chose to add an Army.. " << std::endl;
				return PlaceNewArmies();
			}
            break;
        case c3: //Add 3 Armies
			return PlaceNewArmies();
            break;
        case c4: //Move 4 Armies
			return MoveArmies();
            break;
        case c5: //Move 5 Armies
			return MoveArmies();
            break;
        case c6: //Add 3 Armies (DOUBLE)
			return PlaceNewArmies();
            break;
        case c7: //Move 3 Armies via Ship
			return MoveOverLandOrWater();
            break;
        case c8: //Move 4 Armies
			return MoveArmies();
            break;
        case c9: //Build City
			return BuildCity();
            break;
        case c10: //Add 4 Armies or Move 2 Armies*
			std::cout << "Do you wanna add 4 Armies (press 1) or move 2 Armies (press 2): ";
			while (std::cin >> choice && (choice != 1 && choice != 2)) {
				std::cout << "\nPlease press 1 or 2 to choose your action: ";
			}
			if (choice == 1) {
				std::cout << "You chose to add 4 Armies.. " << std::endl;
				return PlaceNewArmies();
			}
			else {
				std::cout << "You chose to move 2 Armies.. " << std::endl;
				return MoveArmies();
			}
            break;
        case a1: //Move 4 Armies
			return MoveArmies();
            break;
        case a2: //Add 3 Armies or Move 4 Armies
			std::cout << "Do you wanna add 3 Armies (press 1) or move 4 Armies (press 2): ";
			while (std::cin >> choice && (choice != 1 && choice != 2)) {
				std::cout << "\nPlease press 1 or 2 to choose your action: ";
			}
			if (choice == 1) {
				std::cout << "You chose to add 3 Armies.. " << std::endl;
				return PlaceNewArmies();
			}
			else {
				std::cout << "You chose to move 4 Armies.. " << std::endl;
				return MoveArmies();
			}
            break;
        case a3: //Move 5 Armies
			return MoveArmies();
            break;
        case a4: //Add 3 Armies
			return PlaceNewArmies();
            break;
        case a5: //Add 3 Armies
			return PlaceNewArmies();
            break;
        case a6: //Move 3 Armies via Ship
			return MoveOverLandOrWater();
            break;
        case a7: //Build City
			return BuildCity();
            break;
        case a8: //Add 4 Armies or Move 3 Armies
			std::cout << "Do you wanna add 4 Armies (press 1) or move 3 Armies (press 2): ";
			while (std::cin >> choice && (choice != 1 && choice != 2)) {
				std::cout << "\nPlease press 1 or 2 to choose your action: ";
			}
			if (choice == 1) {
				std::cout << "You chose to add 4 Armies.. " << std::endl;
				return PlaceNewArmies();
			}
			else {
				std::cout << "You chose to move 3 Armies.. " << std::endl;
				return MoveArmies();
			}
            break;
        case a9: //Move 4 Armies (DOUBLE)
			return MoveArmies();
            break;
        case o1: //Move 2 Armies
			return MoveArmies();
            break;
        case o2: //Move 3 Armies via Ship
			return MoveOverLandOrWater();
            break;
        case o3: //Move 2 Armies via Ship
			return MoveOverLandOrWater();
            break;
        case o4: //Add 3 Armies
			return PlaceNewArmies();
            break;
        case o5: //Add 3 Armies
			return PlaceNewArmies();
            break;
        case o6: //Add 2 Armies
			return PlaceNewArmies();
            break;
        case o7: //Move 2 Armies via Ship
			return MoveOverLandOrWater();
            break;
        case cr1: //Add 2 Armies
			return PlaceNewArmies();
            break;
        case cr2: //Add 2 Armies
			return PlaceNewArmies();
            break;
        case cr3: //Move 2 Armies
			return MoveArmies();
            break;
        case cr4: //Add 1 Army
			return PlaceNewArmies();
            break;
        case cr5: //Add 2 Armies
			return PlaceNewArmies();
            break;
    }
}

// Place 1 army
bool Actions::PlaceNewArmies()
{
    // Check if player has armies to place
    if (_player->getNumHandArmies() == 0)
    {
        std::cout << "You cannot place any new armies! All of your armies are deployed!" << std::endl;
        return false;
    }

    bool armyPlaced = false;
    while(!armyPlaced)
    {
        unsigned int countryID = 0;
        if (!countryIDUserInput(countryID, "\"Please enter the Country ID"))
        {
            return false;
        }

        auto isStartingCountry = [this](unsigned int countryID) { return countryID == _player->getStartingRegionID(); };
        auto playerHasCityInCountry = [this](CountryNode* node)
            { return std::find(node->CitiesInCountry->begin(), node->CitiesInCountry->end(), _player->getCityColor()) != node->CitiesInCountry->end(); };
        //auto playerAlreadyHasArmyInCountry = [this](CountryNode* node)
        //    { return std::find(node->ArmiesInCountry->begin(), node->ArmiesInCountry->end(), _player->getArmyColor()) != node->ArmiesInCountry->end(); };

        CountryNode* node = _state->GameMap->findCountryByID(countryID);
        // Is starting region or contains city
        if ((isStartingCountry(countryID)
            || playerHasCityInCountry(node))
            /*&& !playerAlreadyHasArmyInCountry(node)*/)
        {
            // decrement num armies in hand
            int numArmies = _player->getNumHandArmies();
            numArmies--;
            _player->setNumHandArmies(numArmies);
            // Add army to country node
            node->ArmiesInCountry->push_back(_player->getArmyColor());

            armyPlaced = true;
        }
        else
        {
            std::cout << "You cant place an army here..." << std::endl;
        }
    }

    return true;
}

bool Actions::MoveArmies(bool canMoveOverWater)
{

    bool armyMoved = false;
    while (!armyMoved)
    {

        unsigned int countryIDSrc = 0;
        unsigned int countryIDDest = 0;

        std::cout << "Moving an army" << std::endl;
        if (!countryIDUserInput(countryIDSrc, "Input the starting country ID"))
        {
            return false;
        }

        if (!countryIDUserInput(countryIDDest, "Input the destination country ID"))
        {
            return false;
        }

        if ((canMoveOverWater && _state->GameMap->areCountriesConnectedByWater(countryIDSrc, countryIDDest)) || _state->GameMap->areCountriesConnected(countryIDSrc, countryIDDest))
        {
            // Can do move

            CountryNode* srcCountry = _state->GameMap->findCountryByID(countryIDSrc);
            CountryNode* destCountry = _state->GameMap->findCountryByID(countryIDDest);

            auto it = std::find(srcCountry->ArmiesInCountry->begin(), srcCountry->ArmiesInCountry->end(), _player->getArmyColor());
            if (it == srcCountry->ArmiesInCountry->end())
            {
                std::cout << "You dont have an army in the starting country..." << std::endl;
                continue;
            }

            srcCountry->ArmiesInCountry->erase(it);
            destCountry->ArmiesInCountry->push_back(_player->getArmyColor());

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

bool Actions::countryIDUserInput(unsigned int &countryID, std::string queryText)
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
        } catch(std::exception& e)
        {
            std::cout << "ID must be a number..." << std::endl;
            continue;
        }

        if (countryID > _state->GameMap->getNumCountries())
        {
            std::cout << "invalid ID range..." << std::endl;
            continue;
        }

        inputTaken = true;
    } while (!inputTaken);

    return true;
}

// Does 1 army, 1 move, card logic will handle the 3 moves
bool Actions::MoveArmies()
{
    return MoveArmies(false);
}

// Does 1 army, 1 move, card logic will handle the 3 moves
bool Actions::MoveOverLandOrWater()
{
    return MoveArmies(true);
}

bool Actions::BuildCity()
{
    // Check if player has cities to place
    if (_player->getNumHandCities() == 0)
    {
        std::cout << "You cannot place any new cities! All of your cities are placed!" << std::endl;
        return false;
    }

    bool cityPlaced = false;
    while(!cityPlaced)
    {
        unsigned int countryID = 0;
        if (!countryIDUserInput(countryID, "\"Please enter the Country ID"))
        {
            return false;
        }

        auto playerHasArmyInCountry = [this](CountryNode* node)
        { return std::find(node->ArmiesInCountry->begin(), node->ArmiesInCountry->end(), _player->getArmyColor()) != node->ArmiesInCountry->end(); };

        CountryNode* node = _state->GameMap->findCountryByID(countryID);
        // Is starting region or contains city
        if (playerHasArmyInCountry(node))
        {
            // decrement num cities in hand
            int numCities = _player->getNumHandCities();
            numCities--;
            _player->setNumHandCities(numCities);

            // Add city to country node
            node->CitiesInCountry->push_back(_player->getCityColor());

            cityPlaced = true;
        }
        else
        {
            std::cout << "You cant place a city here..." << std::endl;
        }
    }

    return true;
}

bool Actions::DestroyArmy()
{
    bool armyDestroyed = false;
    while(!armyDestroyed)
    {
        unsigned int countryID = 0;
        if (!countryIDUserInput(countryID, "Please enter the Country ID"))
        {
            return false;
        }

        CountryNode* node = _state->GameMap->findCountryByID(countryID);
        Armies armyToDestroy;
        if (!node->canDestroyArmy(_player->getArmyColor()))
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

                if (findByValue(armyToDestroy, *_state->GameDeck->ArmiesMap, input))
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

bool Actions::AndOrAction()
{
    return true;
}

bool Actions::Ignore()
{
    std::cout << "Card ignored" << std::endl;
    return true;
}




