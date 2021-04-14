#ifndef GAME_H
#define GAME_H

enum class GuessResponse { TooLow, TooHigh, TakeOff, GameOver };

class CountDown {
public:
    CountDown(unsigned int start);
    void decrement();
    unsigned int value() const;

private:
    unsigned int value_;
};

class SpaceTakeoffGame {
public:
    SpaceTakeoffGame(unsigned int gravity, unsigned int weight);
    GuessResponse make_guess(unsigned int guess);

private:
    const unsigned int gravity;
    const unsigned int weight;
    const unsigned int force;
    CountDown tries_remaining{10};

};

#endif