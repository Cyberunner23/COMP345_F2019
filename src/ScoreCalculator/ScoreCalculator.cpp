#include <ScoreCalculator/ScoreCalculator.h>


ScoreCalculator::ScoreCalculator(GameState* s)
{
  State = s;
}

void ScoreCalculator::CalculateScores()
{

    //int currentScore;
    std::vector<Cards> currentHand;
    std::vector<Armies> regionScores;

    int Forests = 0;
    int Carrots = 0;
    int Anvils = 0;
    int Ores = 0;
    int Crystals = 0;

    //Calculating Scores based on Goods
    //currentScore = 0;

    for (int i = 0; i < State->Players->size(); i++)
    {
        currentHand = *State->Players->at(i).getHand()->HandList;
        //currentScore = 0;

        for (int j = 0; j < currentHand.size(); j++)
        {
            std::string currentGood = State->GameDeck->GoodsMap->at(currentHand.at(j));

            if (currentGood == "Forest")
            {
                Forests++;
            }
            else if (currentGood == "Carrots")
            {
                Carrots++;
            }
            else if (currentGood == "Anvils")
            {
                Anvils++;
            }
            else if (currentGood == "Ore")
            {
                Ores++;
            }
            else if (currentGood == "Crystals")
            {
                Crystals++;
            }
        }

        //Scoring of Forests
        if (Forests >= 6)
        { (*State->Players->at(i).getScore()) += 5; }
        else if (Forests == 5)
        { (*State->Players->at(i).getScore()) += 3; }
        else if (Forests == 4 || Forests == 3)
        { (*State->Players->at(i).getScore()) += 2; }
        else if (Forests == 2)
        { (*State->Players->at(i).getScore()) += 1; }

        //Scoring of Carrots
        if (Carrots >= 8)
        { (*State->Players->at(i).getScore()) += 5; }
        else if (Carrots == 7)
        { (*State->Players->at(i).getScore()) += 3; }
        else if (Carrots == 6 || Carrots == 5)
        { (*State->Players->at(i).getScore()) += 2; }
        else if (Carrots == 4 || Carrots == 3)
        { (*State->Players->at(i).getScore()) += 1; }

        //Scoring of Anvil
        if (Anvils >= 7)
        { (*State->Players->at(i).getScore()) += 5; }
        else if (Anvils == 6)
        { (*State->Players->at(i).getScore()) += 3; }
        else if (Anvils == 5 || Anvils == 4)
        { (*State->Players->at(i).getScore()) += 2; }
        else if (Anvils == 3 || Anvils == 2)
        { (*State->Players->at(i).getScore()) += 1; }
        //Scoring of Ores
        if (Ores >= 5)
        { (*State->Players->at(i).getScore()) += 5; }
        else if (Ores == 4)
        { (*State->Players->at(i).getScore()) += 3; }
        else if (Ores == 3)
        { (*State->Players->at(i).getScore()) += 2; }
        else if (Ores == 2)
        { (*State->Players->at(i).getScore()) += 1; }
        //Scoring of Crystals
        if (Crystals >= 4)
        { (*State->Players->at(i).getScore()) += 5; }
        else if (Crystals == 3)
        { (*State->Players->at(i).getScore()) += 3; }
        else if (Crystals == 2)
        { (*State->Players->at(i).getScore()) += 2; }
        else if (Crystals == 1)
        { (*State->Players->at(i).getScore()) += 1; }

        //*State->Players->at(i).getScore() = currentScore;
    }

    //Calculate Scores based on countries owned
    regionScores = Map::GetInstance().getCountryOwners();
    for (int i = 0; i < State->Players->size(); i++)
    {
        for (int j = 0; j < regionScores.size(); j++)
        {
            if (State->GameDeck->ArmiesMap->at(State->Players->at(i).getArmyColor()) ==
                State->GameDeck->ArmiesMap->at(regionScores.at(j)))
            {
                (*State->Players->at(i).getScore())++;
            }
        }
    }

    //Calculating scores based on continents owned
    regionScores = Map::GetInstance().getContinentOwners();
    for (int i = 0; i < State->Players->size(); i++)
    {
        for (int j = 0; j < regionScores.size(); j++)
        {
            if (State->GameDeck->ArmiesMap->at(State->Players->at(i).getArmyColor()) ==
                State->GameDeck->ArmiesMap->at(regionScores.at(j)))
            {
                (*State->Players->at(i).getScore())++;
            }
        }
    }

    //Calculating highest score
    int currentScore = 0;
    for (int i = 0; i < State->Players->size(); i++)
    {
        if (currentScore < *State->Players->at(i).getScore())
        {
            currentScore = *State->Players->at(i).getScore();
        }
        std::cout << "Player " << i + 1 << " your score is " << *State->Players->at(i).getScore() << std::endl;
    }
    std::cout << "The winning score is: " << currentScore << std::endl;

}
