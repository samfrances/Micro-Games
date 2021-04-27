#include "game.h"
#include <string>
#include <stdexcept>
#include <ios>
#include <istream>

SpaceTakeoffGame::SpaceTakeoffGame(const int gravity, const int weight)
    : gravity_{ gravity },
      weight_{ weight },
      force_{ weight * gravity } {}

GuessResponse SpaceTakeoffGame::make_guess(const Guess& guess) {
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

std::ostream& operator<<(std::ostream& os, const GuessResponse response) {
    switch(response) {
        case GuessResponse::TooHigh: {
            os << std::string{"TOO HIGH, TRY AGAIN"};
            break;
        }
        case GuessResponse::TooLow: {
            os << std::string{"TOO LOW, TRY AGAIN"};
            break;
        }
        case GuessResponse::TakeOff: {
            os << std::string{"GOOD TAKE OFF"};
            break;
        }
        default: {
            os << std::string{"YOU FAILED - THE ALIENS GOT YOU"};
            break;
        }
    }
    return os;
}

Guess::Guess(int value) {
    setValue(value);
}

void Guess::setValue(int value) {
    if (value < 1) throw std::invalid_argument{ "Guess must be a positive integer" };
    value_ = value;
}

std::istream& operator>>(std::istream& is, Guess& guess) {
    int n;
    is >> n;
    if (is.fail()) {
        return is;
    }
    try {
        guess.setValue(n);
    } catch (std::invalid_argument&) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool operator>(const Guess& guess, const int other) {
    return guess.value_ > other;
}

bool operator<(const Guess& guess, const int other) {
    return guess.value_ < other;
}

bool operator>=(const Guess& guess, const int other) {
    return !(guess < other);
}

bool operator<=(const Guess& guess, const int other) {
    return !(guess > other);
}

bool operator==(const Guess& guess, const int other) {
    return !(guess < other || guess > other);
}

bool operator!=(const Guess& guess, const int other) {
    return !(guess == other);
}