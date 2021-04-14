#include <string>
#include "game.h"

SpaceTakeoffGame::SpaceTakeoffGame(unsigned int gravity, unsigned int weight)
    : gravity{ gravity },
      weight{ weight },
      force{ weight * gravity } {}

GuessResponse SpaceTakeoffGame::make_guess(unsigned int guess) {
    if (tries_remaining.value() == 0) {
        over_ = true;
        return GuessResponse::GameOver;
    }
    tries_remaining.decrement();
    if (guess > force) {
        return GuessResponse::TooHigh;
    }
    if (guess < force) {
        return GuessResponse::TooLow;
    }
    over_ = true;
    return GuessResponse::TakeOff;
};

bool SpaceTakeoffGame::over() {
    return over_;
}

CountDown::CountDown(unsigned int start): value_{ start } {}

void CountDown::decrement() {
    if (value_ > 0) {
        value_ -= 1;
    }
}

unsigned int CountDown::value() const {
    return value_;
}

std::string print_response(GuessResponse response) {
    switch(response) {
        case GuessResponse::TooHigh: {
            return "TOO HIGH, TRY AGAIN";
        }
        case GuessResponse::TooLow: {
            return "TOO LOW, TRY AGAIN";
        }
        case GuessResponse::TakeOff: {
            return "GOOD TAKE OFF";
        }
        default: {
            return "YOU FAILED - THE ALIENS GOT YOU";
        }
    }
    return "";
}