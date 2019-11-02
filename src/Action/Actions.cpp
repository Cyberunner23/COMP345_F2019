#include "Actions.hpp"

Actions::Actions(GameState* state, Player* player)
{
    _state = state;
    _player = player;
}

bool Actions::RunAction(Cards card)
{
    switch (card)
    {
        case f1:
            break;
        case f2:
            break;
        case f3:
            break;
        case f4:
            break;
        case f5:
            break;
        case f6:
            break;
        case f7:
            break;
        case f8:
            break;
        case c1:
            break;
        case c2:
            break;
        case c3:
            break;
        case c4:
            break;
        case c5:
            break;
        case c6:
            break;
        case c7:
            break;
        case c8:
            break;
        case c9:
            break;
        case c10:
            break;
        case a1:
            break;
        case a2:
            break;
        case a3:
            break;
        case a4:
            break;
        case a5:
            break;
        case a6:
            break;
        case a7:
            break;
        case a8:
            break;
        case a9:
            break;
        case o1:
            break;
        case o2:
            break;
        case o3:
            break;
        case o4:
            break;
        case o5:
            break;
        case o6:
            break;
        case o7:
            break;
        case cr1:
            break;
        case cr2:
            break;
        case cr3:
            break;
        case cr4:
            break;
        case cr5:
            break;
    }

	return false;
}

// Place 1 army
bool Actions::PlaceNewArmies()
{
    // Check if player has armies to place
    if (*_player->getNumHandArmies() == 0)
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

        auto isStartingCountry = [this](unsigned int countryID) { return countryID == *_player->getStartingRegionID(); };
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
            (*_player->getNumHandArmies())--;
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
    if (*_player->getNumHandCities() == 0)
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
            (*_player->getNumHandCities())--;
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


