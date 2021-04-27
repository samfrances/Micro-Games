#include <gtest/gtest.h>
#include "game.h"

#include <sstream>

TEST(GameTest, Initialization) {
    SpaceTakeoffGame{5, 10};
}

TEST(GameTest, TooHigh) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(Guess{100}),
        GuessResponse::TooHigh
    );
}

TEST(GameTest, OnlyJustTooHigh) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(Guess{51}),
        GuessResponse::TooHigh
    );
}

TEST(GameTest, TooLow) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(Guess{4}),
        GuessResponse::TooLow
    );
}

TEST(GameTest, OnlyJustTooLow) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(Guess{49}),
        GuessResponse::TooLow
    );
}

TEST(GameTest, TakeOff) {
    SpaceTakeoffGame game{5, 10};
    EXPECT_EQ(
        game.make_guess(Guess{50}),
        GuessResponse::TakeOff
    );
}

TEST(GameTest, FinishedAfterTakeOff) {
    SpaceTakeoffGame game{5, 10};
    game.make_guess(Guess{50});
    EXPECT_TRUE(game.over());
}

TEST(GameTest, GameOver) {
    SpaceTakeoffGame game{5, 10};

    for (int i = 0; i < 10; i++) {
        game.make_guess(Guess{100});
    }

    EXPECT_EQ(
        game.make_guess(Guess{51}),
        GuessResponse::GameOver
    );
}

TEST(GameTest, GameNotQuiteOver) {
    SpaceTakeoffGame game{5, 10};

    for (int i = 0; i < 9; i++) {
        game.make_guess(Guess{100});
    }

    EXPECT_NE(
        game.make_guess(Guess{50}),
        GuessResponse::GameOver
    );
}

TEST(GameTest, GameVeryMuchOver) {
    SpaceTakeoffGame game{5, 10};

    for (int i = 0; i < 100; i++) {
        game.make_guess(Guess{100});
    }

    EXPECT_EQ(
        game.make_guess(Guess{51}),
        GuessResponse::GameOver
    );
}

TEST(GameTest, FinishedAferGameOver) {
    SpaceTakeoffGame game{5, 10};

    for (int i = 0; i < 10; i++) {
        game.make_guess(Guess{100});
    }

    game.make_guess(Guess{51});

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

TEST(Guess, SuccessfulConstruction) {
    Guess(10);
}

TEST(Guess, InvalidConstruction) {
    EXPECT_THROW(Guess{-1}, std::invalid_argument);
    EXPECT_THROW(Guess{0}, std::invalid_argument);
}

TEST(Guess, GreaterThan) {
    EXPECT_TRUE(Guess{100} > 10);
    EXPECT_TRUE(Guess{10} > 9);
    EXPECT_FALSE(Guess{49} > 49);
    EXPECT_FALSE(Guess{49} > 50);
}

TEST(Guess, GreaterThanEqual) {
    EXPECT_TRUE(Guess{100} >= 10);
    EXPECT_TRUE(Guess{10} >= 9);
    EXPECT_TRUE(Guess{49} >= 49);
    EXPECT_FALSE(Guess{49} >= 50);
    EXPECT_FALSE(Guess{49} >= 100);
}

TEST(Guess, LessThan) {
    EXPECT_TRUE(Guess{10} < 100);
    EXPECT_TRUE(Guess{9} < 10);
    EXPECT_FALSE(Guess{49} < 49);
    EXPECT_FALSE(Guess{50} < 49);
}

TEST(Guess, LessThanEqual) {
    EXPECT_TRUE(Guess{33} <= 100);
    EXPECT_TRUE(Guess{33} <= 34);
    EXPECT_TRUE(Guess{33} <= 33);
    EXPECT_FALSE(Guess{33} <= 32);
    EXPECT_FALSE(Guess{33} <= 10);
}

TEST(Guess, Equal) {
    EXPECT_TRUE(Guess{33} == 33);
    EXPECT_TRUE(Guess{387} == 387);
    EXPECT_FALSE(Guess{387} == 386);
    EXPECT_FALSE(Guess{387} == 388);
    EXPECT_FALSE(Guess{2} == 4);
}

TEST(Guess, NotEqual) {
    EXPECT_FALSE(Guess{33} != 33);
    EXPECT_FALSE(Guess{387} != 387);
    EXPECT_TRUE(Guess{387} != 386);
    EXPECT_TRUE(Guess{387} != 388);
    EXPECT_TRUE(Guess{2} != 4);
}

TEST(Guess, RightStream_Fail_NotANumber) {
    std::istringstream in{"foo"};
    Guess guess{1};
    in >> guess;
    EXPECT_TRUE(in.fail());
}

TEST(Guess, RightStream_Fail_Zero) {
    std::istringstream in{"0"};
    Guess guess{1};
    in >> guess;
    EXPECT_TRUE(in.fail());
}

TEST(Guess, RightStream_Fail_Negative) {
    std::istringstream in{"-1"};
    Guess guess{1};
    in >> guess;
    EXPECT_TRUE(in.fail());
}

TEST(Guess, RightStream_Succeed) {
    std::istringstream in{"10"};
    Guess guess{1};
    in >> guess;
    EXPECT_FALSE(in.fail());
    EXPECT_EQ(guess, 10);
}