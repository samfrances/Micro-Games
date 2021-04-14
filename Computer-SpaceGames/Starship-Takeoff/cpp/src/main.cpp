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

    SpaceTakeoffGame game(gravity, weight);

    std::cout << "STARSHIP TAKE-OFF" << std::endl;
    std::cout << "GRAVITY=" << gravity << std::endl;
    std::cout << "TYPE IN FORCE" << std::endl;
    while (true) {
        unsigned int guess;  
        std::cin >> guess;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cout << "INVALID NUMBER, TRY AGAIN" << std::endl;
            continue;
        }
        std::cout << print_response(game.make_guess(guess)) << std::endl;
        if (game.over()) {
            break;
        }
    }
}
