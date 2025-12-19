#include <string>
#include "gtest/gtest.h"
#include "Knight.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "Inventory.hpp"

// Test fixture for Knight tests
class KnightTest : public ::testing::Test {
 protected:
    Knight* knight;
    Player* player;
    Room* armory;

    void SetUp() override {
        knight = new Knight();
        player = new Player();
        armory = new Room("Armory", "A room full of weapons");

        // Add knight to room and player to room
        armory->addWorldObject(knight);
        player->setCurrentRoom(armory);
    }

    void TearDown() override {
        delete player;
        delete armory;
    }
};

// Initial State Tests

TEST_F(KnightTest, InitialStateNotSolved) {
    // Knight should not have given sword initially
    EXPECT_FALSE(knight->hasGivenSword());
}

TEST_F(KnightTest, InitialInteractionAsksRiddle) {
    std::string response = knight->interact(*player);

    // Should contain riddle text
    EXPECT_NE(response.find("riddle"), std::string::npos);
    EXPECT_NE(response.find("mine"), std::string::npos);
    EXPECT_NE(response.find("wooden case"), std::string::npos);
}

// Riddle Solving Tests

TEST_F(KnightTest, SolveRiddleWithPencil) {
    EXPECT_TRUE(knight->solveRiddle("pencil"));
}

TEST_F(KnightTest, SolveRiddleWithLead) {
    EXPECT_TRUE(knight->solveRiddle("lead"));
}

TEST_F(KnightTest, SolveRiddleWithPencilLead) {
    EXPECT_TRUE(knight->solveRiddle("pencil lead"));
}

TEST_F(KnightTest, SolveRiddleWithArticle) {
    EXPECT_TRUE(knight->solveRiddle("a pencil"));
}

TEST_F(KnightTest, SolveRiddleCaseInsensitive) {
    EXPECT_TRUE(knight->solveRiddle("PENCIL"));

    Knight knight2;
    EXPECT_TRUE(knight2.solveRiddle("Pencil"));

    Knight knight3;
    EXPECT_TRUE(knight3.solveRiddle("PeNcIl"));
}

TEST_F(KnightTest, SolveRiddleWrongAnswer) {
    EXPECT_FALSE(knight->solveRiddle("sword"));
    EXPECT_FALSE(knight->solveRiddle("key"));
    EXPECT_FALSE(knight->solveRiddle("coal"));
    EXPECT_FALSE(knight->solveRiddle("diamond"));
}

TEST_F(KnightTest, SolveRiddleEmptyString) {
    EXPECT_FALSE(knight->solveRiddle(""));
}

TEST_F(KnightTest, SolveRiddlePartialAnswer) {
    EXPECT_FALSE(knight->solveRiddle("pen"));
    EXPECT_FALSE(knight->solveRiddle("cil"));
}

// Sword Giving Tests

TEST_F(KnightTest, InteractAfterSolvingGivesSword) {
    // Solve riddle first
    knight->solveRiddle("pencil");

    // Interact should give sword
    std::string response = knight->interact(*player);

    EXPECT_NE(response.find("sword"), std::string::npos);
    EXPECT_NE(response.find("proven"), std::string::npos);

    // Sword should be in the room now
    Item* sword = armory->removeItem("sword");
    ASSERT_NE(sword, nullptr);
    EXPECT_EQ(sword->getName(), "Sword");

    // Clean up
    delete sword;
}

TEST_F(KnightTest, HasGivenSwordAfterGiving) {
    knight->solveRiddle("pencil");
    knight->interact(*player);

    EXPECT_TRUE(knight->hasGivenSword());
}

TEST_F(KnightTest, InteractAfterSwordGivenAcknowledges) {
    knight->solveRiddle("pencil");
    knight->interact(*player);  // First interaction gives sword

    std::string response = knight->interact(*player);  // Second interaction

    EXPECT_NE(response.find("worthy"), std::string::npos);
    EXPECT_NE(response.find("proven"), std::string::npos);
}

TEST_F(KnightTest, OnlyGivesSwordOnce) {
    knight->solveRiddle("pencil");
    knight->interact(*player);  // First time - gives sword

    // Remove the sword from room
    Item* firstSword = armory->removeItem("sword");
    ASSERT_NE(firstSword, nullptr);
    delete firstSword;

    knight->interact(*player);  // Second time - should not give another

    // Should not create another sword
    Item* secondSword = armory->removeItem("sword");
    EXPECT_EQ(secondSword, nullptr);
}

// Multiple Solve Attempts

TEST_F(KnightTest, WrongAnswerThenCorrectAnswer) {
    EXPECT_FALSE(knight->solveRiddle("sword"));
    EXPECT_FALSE(knight->hasGivenSword());

    EXPECT_TRUE(knight->solveRiddle("pencil"));

    knight->interact(*player);
    EXPECT_TRUE(knight->hasGivenSword());
}

TEST_F(KnightTest, MultipleWrongAnswers) {
    EXPECT_FALSE(knight->solveRiddle("sword"));
    EXPECT_FALSE(knight->solveRiddle("key"));
    EXPECT_FALSE(knight->solveRiddle("iron"));
    EXPECT_FALSE(knight->hasGivenSword());
}

TEST_F(KnightTest, CannotUnsolvePuzzle) {
    knight->solveRiddle("pencil");
    knight->interact(*player);
    EXPECT_TRUE(knight->hasGivenSword());

    // Even if we try wrong answer after, should still have given sword
    knight->solveRiddle("wrong");
    EXPECT_TRUE(knight->hasGivenSword());
}

// Integration test

TEST_F(KnightTest, FullGameplaySequence) {
    // 1. Player enters room, talks to knight
    std::string response1 = knight->interact(*player);
    EXPECT_NE(response1.find("riddle"), std::string::npos);
    EXPECT_FALSE(knight->hasGivenSword());

    // 2. Player tries wrong answer
    EXPECT_FALSE(knight->solveRiddle("sword"));

    // 3. Player solves riddle
    EXPECT_TRUE(knight->solveRiddle("pencil"));

    // 4. Player talks to knight again, gets sword
    std::string response2 = knight->interact(*player);
    EXPECT_NE(response2.find("sword"), std::string::npos);
    EXPECT_TRUE(knight->hasGivenSword());

    // 5. Player picks up sword
    player->pickUpItem("sword");
    EXPECT_TRUE(player->getInventory()->hasItem("sword"));

    // 6. Player talks to knight one more time
    std::string response3 = knight->interact(*player);
    EXPECT_NE(response3.find("worthy"), std::string::npos);
}
