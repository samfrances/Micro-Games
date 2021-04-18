#include "game.h"
#include <string>

SpaceTakeoffGame::SpaceTakeoffGame(const int gravity, const int weight)
    : gravity_{ gravity },
      weight_{ weight },
      force_{ weight * gravity } {}

GuessResponse SpaceTakeoffGame::make_guess(const int guess) {
    if (tries_remaining_.is_finished()) {
        over_ = true;
        return GuessResponse::GameOver;
    }
    tries_remaining_.decrement();
    if (guess > force_) {
        return GuessResponse::TooHigh;
    }
    if (guess < force_) {
        return GuessResponse::TooLow;
    }
    over_ = true;
    return GuessResponse::TakeOff;
}

bool SpaceTakeoffGame::over() const {
    return over_;
}

CountDown::CountDown(const int start): value_{ start } {}

void CountDown::decrement() {
    if (value_ > 0) {
        value_ -= 1;
    }
}

bool CountDown::is_finished() const {
    return value_ == 0;
}

std::string print_response(const GuessResponse response) {
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