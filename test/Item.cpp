#include <gtest/gtest.h>
#include "Item.hpp"
#include "WorldObject.hpp"
#include "Exit.hpp"

// Test class for Item
class ItemTest : public ::testing::Test {
 protected:
    Item* item;

    void SetUp() override {
        item = new Item("item123", "Golden Key", "A shiny golden key.");
    }

    void TearDown() override {
        delete item;
    }
};

// Test the constructor and getters
TEST_F(ItemTest, ConstructorAndGettersTest) {
    EXPECT_EQ(item->getId(), "item123");
    EXPECT_EQ(item->getName(), "Golden Key");
}

// Test the examine method
TEST_F(ItemTest, ExamineTest) {
    EXPECT_EQ(item->examine(), "A shiny golden key.");
}
