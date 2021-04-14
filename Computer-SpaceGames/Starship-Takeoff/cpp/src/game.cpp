#include "game.h"

SpaceTakeoffGame::SpaceTakeoffGame(unsigned int gravity, unsigned int weight)
    : gravity{ gravity },
      weight{ weight },
      force{ weight * gravity } {}

GuessResponse SpaceTakeoffGame::make_guess(unsigned int guess) {
    if (tries_remaining.value() == 0) {
        return GuessResponse::GameOver;
    }
    tries_remaining.decrement();
    if (guess > force) {
        return GuessResponse::TooHigh;
    }
    if (guess < force) {
        return GuessResponse::TooLow;
    }
    return GuessResponse::TakeOff;
};

CountDown::CountDown(unsigned int start): value_{ start } {}

void CountDown::decrement() {
    if (value_ > 0) {
        value_ -= 1;
    }
}

unsigned int CountDown::value() const {
    return value_;
}
