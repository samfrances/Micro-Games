#include <gtest/gtest.h>
#include "game.h"

TEST(GameTest, Initialization) {
    SpaceTakeoffGame{5, 10};
}

TEST(GameTest, TooHigh) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(100),
        GuessResponse::TooHigh
    );
}

TEST(GameTest, OnlyJustTooHigh) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(51),
        GuessResponse::TooHigh
    );
}

TEST(GameTest, TooLow) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(4),
        GuessResponse::TooLow
    );
}

TEST(GameTest, OnlyJustTooLow) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(49),
        GuessResponse::TooLow
    );
}

TEST(GameTest, TakeOff) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(50),
        GuessResponse::TakeOff
    );
}

TEST(GameTest, GameOver) {
    SpaceTakeoffGame game{5, 10};

    for (int i = 0; i < 10; i++) {
        game.make_guess(100);
    }

    EXPECT_EQ(
        game.make_guess(51),
        GuessResponse::GameOver
    );
}

TEST(GameTest, GameNotQuiteOver) {
    SpaceTakeoffGame game{5, 10};

    for (int i = 0; i < 9; i++) {
        game.make_guess(100);
    }

    EXPECT_NE(
        game.make_guess(50),
        GuessResponse::GameOver
    );
}

TEST(GameTest, GameVeryMuchOver) {
    SpaceTakeoffGame game{5, 10};

    for (int i = 0; i < 100; i++) {
        game.make_guess(100);
    }

    EXPECT_EQ(
        game.make_guess(51),
        GuessResponse::GameOver
    );
}