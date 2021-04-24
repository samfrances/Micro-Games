#include <gtest/gtest.h>
#include "game.h"

#include <sstream>

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

TEST(GameTest, FinishedAfterTakeOff) {
    SpaceTakeoffGame game{5, 10};
    game.make_guess(50);
    EXPECT_TRUE(game.over());
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

TEST(GameTest, FinishedAferGameOver) {
    SpaceTakeoffGame game{5, 10};

    for (int i = 0; i < 10; i++) {
        game.make_guess(100);
    }

    game.make_guess(51);

    EXPECT_TRUE(game.over());
}

TEST(StreamResponseTests, TooHigh) {
    std::stringstream out;
    out << GuessResponse::TooHigh;
    EXPECT_EQ(
        out.str(),
        "TOO HIGH, TRY AGAIN"
    );
}

TEST(StreamResponseTests, TooLow) {
    std::stringstream out;
    out << GuessResponse::TooLow;
    EXPECT_EQ(
        out.str(),
        "TOO LOW, TRY AGAIN"
    );
}

TEST(StreamResponseTests, TakeOff) {
    std::stringstream out;
    out << GuessResponse::TakeOff;
    EXPECT_EQ(
        out.str(),
        "GOOD TAKE OFF"
    );
}

TEST(StreamResponseTests, GameOver) {
    std::stringstream out;
    out << GuessResponse::GameOver;
    EXPECT_EQ(
        out.str(),
        "YOU FAILED - THE ALIENS GOT YOU"
    );
}