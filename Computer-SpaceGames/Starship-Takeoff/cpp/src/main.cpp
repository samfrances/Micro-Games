#include <iostream>
#include <random>
#include "game.h"

int main(int argc, char const *argv[])
{
  std::random_device rd;
  std::mt19937_64 eng(rd());

  std::uniform_int_distribution<unsigned int> gravity_distr{1, 20};
  std::uniform_int_distribution<unsigned int> weight_distr{1, 40};

  auto gravity =  gravity_distr(eng);
  auto weight =  weight_distr(eng);

  std::cout << gravity << std::endl;
  std::cout << weight << std::endl;

  SpaceTakeoffGame game(gravity, weight);

  std::cout << "STARSHIP TAKE-OFF" << std::endl;
  std::cout << "GRAVITY=" << gravity << std::endl;
  std::cout << "TYPE IN FORCE" << std::endl;
  while (true) {
    unsigned int guess;  
    std::cin >> guess;
    switch(game.make_guess(guess)) {
      case GuessResponse::TooHigh: {
        std::cout << "TOO HIGH, TRY AGAIN" << std::endl;
        break;
      }
      case GuessResponse::TooLow: {
        std::cout << "TOO LOW, TRY AGAIN" << std::endl;
        break;
      }
      case GuessResponse::TakeOff: {
        std::cout << "GOOD TAKE OFF" << std::endl;
        return 0;
      }
      case GuessResponse::GameOver: {
        std::cout << "YOU FAILED - THE ALIENS GOT YOU" << std::endl;
        return 0;
      }
    } 
  }
}
