#include "Deck.h"

int main() {
  std::string response;


 unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
 std::shuffle(Deck.begin(), Deck.end(), std::default_random_engine(seed));

  std::cout <<  "You Have Drawn: " << DeckMap[draw()] << std::endl;
  std::cout << "Draw again? Y/N" << std::endl;
  std::cin >> response;

  while(response != "n")
  {

    std::cout <<  "You Have Drawn: " << DeckMap[draw()] << std::endl;
    std::cout << "Draw again? Y/N" << std::endl;
    std::cin >> response;

  }


  return 0;
};
