#include <ScoreCalculator.h>


ScoreCalculator::ScoreCalculator(GameState* s)
{
  State = s;
  currentHand = new std::vector<Cards>();
  regionScores = new std::vector<Armies>();


  *Forests = 0;
  *Carrots = 0;
  *Anvils = 0;
  *Ores = 0;
  *Crystals = 0;
  *currentScore = 0;
}

void CalculateScores
{

  //Calculating Scores based on Goods
  *Forests = 0;
  *Carrots = 0;
  *Anvils = 0;
  *Ores = 0;
  *Crystals = 0;
  *currentScore = 0;

  for(int i = 0; i < state.Players->size(); i++)
  {
      currentHand = state->Players -> at(i)->getHand();
      curretScore = state->Players -> at(i)->getScore();

      for(int j = 0; j < currentHand->size(); j++)
      {
          switch(s -> GameDeck -> GoodsMap -> at(currentHand -> at(j))
          {
            case "Forest":
            *Forests += 1;
            break;

            case "Carrots":
            *Carrots += 1;
            break;

            case "Anvils":
            *Anvils += 1;
            break;

            case "Ore":
            *Ore += 1;
            break;

            case "Crystals":
            *Crystals += 1;
            break;

            default: break;
          }
      }

      //Scoring of Forests
      if(*Forests >= 6 ) {currentScore += 5}
      else if(*Forests == 5){currentScore += 3}
      else if(*Forests == 4 || *Forests == 3){currentScore += 2}
      else if(*Forests == 2){currentScore += 1}

      //Scoring of Carrots
      if(*Carrots >= 8 ) {currentScore += 5}
      else if(*Carrots == 7){currentScore += 3}
      else if(*Carrots == 6 || *Carrots == 5){currentScore += 2}
      else if(*Carrots == 4 || *Carrots == 3){currentScore += 1}

      //Scoring of Anvil
      if(*Anvils >= 7 ) {currentScore += 5}
      else if(*Anvils == 6){currentScore += 3}
      else if(*Anvils == 5 || *Anvils == 4){currentScore += 2}
      else if(*Anvils == 3 || *Anvils == 2){currentScore += 1}
      //Scoring of Ores
      if(*Ores >= 5 ) {currentScore += 5}
      else if(*Ores == 4){currentScore += 3}
      else if(*Ores == 3){currentScore += 2}
      else if(*Ores == 2){currentScore += 1}
      //Scoring of Crystals
      if(*Crystals >= 4 ) {currentScore += 5}
      else if(*Crystals == 3){currentScore += 3}
      else if(*Crystals == 2){currentScore += 2}
      else if(*Crystals == 1){currentScore += 1}

      state->Players->at(i) ->setScore(currentScore);

  }
  //Calculate Scores based on countries owned
regionScores = state->Map->getCountryOwners();
for(int i = 0; i < state->Players->size(); i++)
{
  curretScore = state->Players -> at(i)->getScore();
  for(int j = 0; j < regionScores->size(); j++)
  {
    if(state->GameDeck->ArmiesMap->at(state->Players -> at(i)) == state->GameDeck->ArmiesMap->at(regionScores -> at(j)))
    {
      curentScore ++;
    }
    state -> Players -> at(i) ->setScore(currentScore);
  }
}

//Calculating scores based on continents owned
regionScores = state->Map->getContinentOwners();
for(int i = 0; i < state->Players->size(); i++)
{
  curretScore = state->Players -> at(i)->getScore();
  for(int j = 0; j < regionScores->size(); j++)
  {
    if(state->GameDeck->ArmiesMap->at(state->Players -> at(i)) == state->GameDeck->ArmiesMap->at(regionScores -> at(j)))
    {
      curentScore ++;
    }
    state -> Players -> at(i) ->setScore(currentScore);
  }
}

//Calculating highest score
*currentScore = 0;
for(int i = 0; i < state->Players->size(); i++)
{
  if(currentScore < state->Players -> at(i)->getScore())
  {
    currentScore = state->Players -> at(i)->getScore();
  }
  std::cout << "Player " << i+1 << " your score is " << Players -> at(i)->getScore() << std::endl;
}
std::cout << "The winning score is: " << currentScore << std::endl;

}
