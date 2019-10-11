#include "Deck.h"

int main() {
  std::string response;


  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(Deck.begin(), Deck.end(), std::default_random_engine(seed));

  Cards c = draw();
  std::cout <<  "You Have Drawn: " << DeckMap[draw()] << ", Cost: "<< c <<std::endl;
  std::cout << "Draw again? Y/N" << std::endl;
  std::cin >> response;

  while(response != "n")
  {
    c = draw();
    std::cout <<  "You Have Drawn: " << DeckMap[c] << ", Cost: "<< c << std::endl;
    std::cout << "Draw again? Y/N" << std::endl;
    std::cin >> response;

  }

  std::cout << "Your hand is: " << std::endl;
  for(int i = 0; i < Hand.size(); i++)
  {
    std::cout << DeckMap[Hand[i]] << ", Cost: "<< Hand[i] <<std::endl;
  }

  return 0;
};
