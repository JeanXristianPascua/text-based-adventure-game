#include <gtest/gtest.h>
#include "Fountain.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "Item.hpp"

// Test class for Fountain interactions
class FountainTest : public ::testing::Test {
 protected:
    Player* player;
    Fountain* fountain;

    void SetUp() override {
        player = new Player();
        fountain = new Fountain();
    }

    void TearDown() override {
        delete player;
        delete fountain;
    }
};

// Test for first interaction adding the Healing Herb to the player's inventory
TEST_F(FountainTest, NoRoomReturnsMessage) {
    std::string result = fountain->interact(*player);

    EXPECT_EQ(result, "You search the fountain but find nothing.");
}
