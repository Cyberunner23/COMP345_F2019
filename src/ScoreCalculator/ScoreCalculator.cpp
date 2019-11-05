#include <ScoreCalculator/ScoreCalculator.h>


ScoreCalculator::ScoreCalculator(GameState* s)
{
  State = s;
}

void ScoreCalculator::CalculateScores()
{

    int currentScore;
    std::vector<Cards> currentHand;
    std::vector<Armies> regionScores;

    int Forests = 0;
    int Carrots = 0;
    int Anvils = 0;
    int Ores = 0;
    int Crystals = 0;

  //Calculating Scores based on Goods
  currentScore = 0;

  for(int i = 0; i < State->Players->size(); i++)
  {
      currentHand = *State->Players->at(i).getHand()->HandList;
      currentScore = *State->Players->at(i).getScore();

      for(int j = 0; j < currentHand.size(); j++)
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
      if(Forests >= 6 ) {currentScore += 5;}
      else if(Forests == 5){currentScore += 3;}
      else if(Forests == 4 || Forests == 3){currentScore += 2;}
      else if(Forests == 2){currentScore += 1;}

      //Scoring of Carrots
      if(Carrots >= 8 ) {currentScore += 5;}
      else if(Carrots == 7){currentScore += 3;}
      else if(Carrots == 6 || Carrots == 5){currentScore += 2;}
      else if(Carrots == 4 || Carrots == 3){currentScore += 1;}

      //Scoring of Anvil
      if(Anvils >= 7 ) {currentScore += 5;}
      else if(Anvils == 6){currentScore += 3;}
      else if(Anvils == 5 || Anvils == 4){currentScore += 2;}
      else if(Anvils == 3 || Anvils == 2){currentScore += 1;}
      //Scoring of Ores
      if(Ores >= 5 ) {currentScore += 5;}
      else if(Ores == 4){currentScore += 3;}
      else if(Ores == 3){currentScore += 2;}
      else if(Ores == 2){currentScore += 1;}
      //Scoring of Crystals
      if(Crystals >= 4 ) {currentScore += 5;}
      else if(Crystals == 3){currentScore += 3;}
      else if(Crystals == 2){currentScore += 2;}
      else if(Crystals == 1){currentScore += 1;}

      State->Players->at(i).setScore(&currentScore);

  }
  //Calculate Scores based on countries owned
regionScores = State->GameMap->getCountryOwners();
for(int i = 0; i < State->Players->size(); i++)
{
  currentScore = *State->Players->at(i).getScore();
  for(int j = 0; j < regionScores.size(); j++)
  {
    if(State->GameDeck->ArmiesMap->at(State->Players->at(i).getArmyColor()) == State->GameDeck->ArmiesMap->at(regionScores.at(j)))
    {
        currentScore++;
    }
    State -> Players -> at(i).setScore(&currentScore);
  }
}

//Calculating scores based on continents owned
regionScores = State->GameMap->getContinentOwners();
for(int i = 0; i < State->Players->size(); i++)
{
  currentScore = *State->Players -> at(i).getScore();
  for(int j = 0; j < regionScores.size(); j++)
  {
    if(State->GameDeck->ArmiesMap->at(State->Players->at(i).getArmyColor()) == State->GameDeck->ArmiesMap->at(regionScores.at(j)))
    {
        currentScore++;
    }
    State -> Players -> at(i).setScore(&currentScore);
  }
}

//Calculating highest score
currentScore = 0;
for(int i = 0; i < State->Players->size(); i++)
{
  if(currentScore < *State->Players->at(i).getScore())
  {
    currentScore = *State->Players -> at(i).getScore();
  }
  std::cout << "Player " << i+1 << " your score is " << State->Players->at(i).getScore() << std::endl;
}
std::cout << "The winning score is: " << currentScore << std::endl;

}
