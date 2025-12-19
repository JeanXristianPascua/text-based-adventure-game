#include <gtest/gtest.h>
#include "BookPile.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "Item.hpp"

// Test class for BookPile interactions
class BookPileTest : public ::testing::Test {
 protected:
    Player* player;
    Room* room;
    BookPile* bookPile;

    void SetUp() override {
        player = new Player();
        room = new Room("TestRoom", "A dusty old room full of books.");
        bookPile = new BookPile();

        player->setCurrentRoom(room);
    }

    void TearDown() override {
        delete player;
        delete room;
        delete bookPile;
    }
};

// Test for first interaction adding the Prison Key to the room
TEST_F(BookPileTest, FirstInteractionAddsPrisonKey) {
    EXPECT_FALSE(room->removeItem("prison key"));

    std::string result = bookPile->interact(*player);

    EXPECT_EQ(result, "You search through the pile of dusty books...\n"
                       "Hidden among the pages, you find a Prison Key!\n"
                       "You should take it.");
}

// Test for subsequent interactions when the Prison Key is already taken
TEST_F(BookPileTest, NoRoomReturnsMessage) {
    player->setCurrentRoom(nullptr);

    std::string result = bookPile->interact(*player);

    EXPECT_EQ(result, "You search the books but find nothing.");
}
