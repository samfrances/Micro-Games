#ifndef GAME_H
#define GAME_H

#include <string>

enum class GuessResponse { TooLow, TooHigh, TakeOff, GameOver };

std::ostream& operator<<(std::ostream& os, const GuessResponse response);

class CountDown {
public:
    CountDown(int start);
    void decrement();
    bool is_finished() const;

private:
    int value_;
};

class Guess final {
public:
    Guess() {};
    Guess(int value);
    void setValue(int value);
    friend bool operator>(const Guess& guess, const int other);
    friend bool operator<(const Guess& guess, const int other);
    friend bool operator>=(const Guess& guess, const int other);
    friend bool operator<=(const Guess& guess, const int other);
    friend bool operator==(const Guess& guess, const int other);
    friend bool operator!=(const Guess& guess, const int other);
private:
    int value_{1};
};

std::istream& operator>>(std::istream& is, Guess& guess);

class SpaceTakeoffGame {
public:
    SpaceTakeoffGame(int gravity, int weight);
    GuessResponse make_guess(const Guess& guess);
    bool over() const;

private:
    const int gravity_;
    const int weight_;
    const int force_;
    CountDown tries_remaining_{10};
    bool over_{false};

};

#endif