#include <iostream>
#include <random>
#include <limits>
#include <ios>
#include "game.h"

int main()
{
    std::random_device rd;
    std::mt19937_64 eng(rd());

    std::uniform_int_distribution<int> gravity_distr{1, 20};
    std::uniform_int_distribution<int> weight_distr{1, 40};

    const auto gravity =  gravity_distr(eng);
    const auto weight =  weight_distr(eng);

    SpaceTakeoffGame game(gravity, weight);

    std::cout << "STARSHIP TAKE-OFF\n"
              << "GRAVITY=" << gravity << "\n"
              << "TYPE IN FORCE" << std::endl;
    do {
        int guess;
        std::cin >> guess;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "INVALID GUESS, TRY AGAIN" << std::endl;
            continue;
        }
        std::cout << game.make_guess(guess) << std::endl;
    } while (!game.over());
    return 0;
}
