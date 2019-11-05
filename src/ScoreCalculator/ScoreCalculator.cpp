#include <ScoreCalculator.h>


ScoreCalculator::ScoreCalculator(GameState* s)
{
  State = s;
  Scores = new std::vector<int>();
  currentHand = new std::vector<Cards>();


  *Forests = 0;
  *Carrots = 0;
  *Anvils = 0;
  *Ores = 0;
  *Crystals = 0;
  *currentScore = 0;
}

void CalculateScores
{
  *Forests = 0;
  *Carrots = 0;
  *Anvils = 0;
  *Ores = 0;
  *Crystals = 0;
  *currentScore = 0;

  for(int i = 0; i < state.Players->size(); i++)
  {
      currentHand = state.Players -> at(i).getHand();

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

      Scores -> push_back(currentScore);
  }

}
