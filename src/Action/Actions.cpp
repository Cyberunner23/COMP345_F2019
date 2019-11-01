#include "Actions.hpp"

Actions::Actions(GameState* state, Player* player)
{
    _state = state;
    _player = player;
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
        std::string input;
        std::cout << "Placing a new army." << std::endl;
        std::cout << "Please enter the Country ID (q/Q to cancel): ";
        std::cin >> input;

        if (input == "q" || input == "Q")
        {
            std::cout << "Place Army canceled" << std::endl;
            return false;
        }

        unsigned int countryID = 0;
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

        auto isStartingCountry = [this](unsigned int countryID) { return countryID == *_player->getStartingRegionID(); };
        auto playerHasCityInCountry = [this](CountryNode* node)
            { return std::find(node->CitiesInCountry->begin(), node->CitiesInCountry->end(), _player->getCityColor()) != node->CitiesInCountry->end(); };
        auto playerAlreadyHasArmyInCountry = [this](CountryNode* node)
            { return std::find(node->ArmiesInCountry->begin(), node->ArmiesInCountry->end(), _player->getArmyColor()) != node->ArmiesInCountry->end(); };

        CountryNode* node = _state->GameMap->findCountryByID(countryID);
        // Is starting region or contains city
        if ((isStartingCountry(countryID)
            || playerHasCityInCountry(node))
            && !playerAlreadyHasArmyInCountry(node))
        {
            // decrement num armies in hand
            (*_player->getNumHandArmies())--;
            // Add army to country node
            node->ArmiesInCountry->push_back(_player->getArmyColor());

            armyPlaced = true;
        }
        else
        {
            std::cout << "You cant place a city here..." << std::endl;
        }
    }

    return true;
}

bool Actions::MoveArmies()
{
    return true;
}

bool Actions::MoveOverLand()
{
    return true;
}

bool Actions::MoveOverWater()
{
    return true;
}

bool Actions::BuildCity()
{

    return true;
}

bool Actions::DestroyArmy()
{
    bool armyDestroyed = false;
    while(!armyDestroyed)
    {
        std::string input;
        std::cout << "Destroying an army." << std::endl;
        std::cout << "Please enter the Country ID (q/Q to cancel): ";
        std::cin >> input;

        if (input == "q" || input == "Q")
        {
            std::cout << "Place Army canceled" << std::endl;
            return false;
        }

        unsigned int countryID = 0;
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


