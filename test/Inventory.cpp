#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "Inventory.hpp"
#include "Item.hpp"

// Test fixture for Inventory tests
class InventoryTest : public ::testing::Test {
 protected:
    Inventory* inventory;

    void SetUp() override {
        inventory = new Inventory();
    }

    void TearDown() override {
        delete inventory;
    }
};

// Basic item management tests

TEST_F(InventoryTest, NewInventoryIsEmpty) {
    EXPECT_TRUE(inventory->isEmpty());
    EXPECT_EQ(inventory->getItemCount(), 0);
}

TEST_F(InventoryTest, AddItemSuccess) {
    Item sword("sword", "Sword", "A sharp blade");

    EXPECT_TRUE(inventory->addItem(sword));
    EXPECT_FALSE(inventory->isEmpty());
    EXPECT_EQ(inventory->getItemCount(), 1);
}

TEST_F(InventoryTest, AddDuplicateItemFails) {
    Item sword1("sword", "Sword", "A sharp blade");
    Item sword2("sword", "Sword", "Another sword");

    EXPECT_TRUE(inventory->addItem(sword1));
    EXPECT_FALSE(inventory->addItem(sword2));  // Should fail - duplicate ID
    EXPECT_EQ(inventory->getItemCount(), 1);
}

TEST_F(InventoryTest, HasItemById) {
    Item sword("sword", "Sword", "A sharp blade");
    inventory->addItem(sword);

    EXPECT_TRUE(inventory->hasItem("sword"));
    EXPECT_FALSE(inventory->hasItem("shield"));
}

TEST_F(InventoryTest, HasItemByName) {
    Item sword("sword_id", "Sword", "A sharp blade");
    inventory->addItem(sword);

    EXPECT_TRUE(inventory->hasItemByName("Sword"));
    EXPECT_FALSE(inventory->hasItemByName("Shield"));
}

TEST_F(InventoryTest, GetItemById) {
    Item sword("sword", "Sword", "A sharp blade");
    inventory->addItem(sword);

    Item& retrieved = inventory->getItem("sword");
    EXPECT_EQ(retrieved.getId(), "sword");
    EXPECT_EQ(retrieved.getName(), "Sword");
}

TEST_F(InventoryTest, GetItemByName) {
    Item sword("sword_id", "Sword", "A sharp blade");
    inventory->addItem(sword);

    Item* retrieved = inventory->getItemByName("Sword");
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getName(), "Sword");
    EXPECT_EQ(retrieved->getId(), "sword_id");
}

TEST_F(InventoryTest, GetItemByNameNotFound) {
    Item* retrieved = inventory->getItemByName("Nonexistent");
    EXPECT_EQ(retrieved, nullptr);
}

TEST_F(InventoryTest, RemoveItem) {
    Item sword("sword", "Sword", "A sharp blade");
    inventory->addItem(sword);

    EXPECT_TRUE(inventory->removeItem("sword"));
    EXPECT_FALSE(inventory->hasItem("sword"));
    EXPECT_TRUE(inventory->isEmpty());
}

TEST_F(InventoryTest, RemoveNonexistentItem) {
    EXPECT_FALSE(inventory->removeItem("nonexistent"));
}

TEST_F(InventoryTest, GetAllItems) {
    Item sword("sword", "Sword", "A sharp blade");
    Item key("key", "Key", "An old key");

    inventory->addItem(sword);
    inventory->addItem(key);

    std::vector<Item*> items = inventory->getAllItems();
    EXPECT_EQ(items.size(), 2);
}

// Item combination tests

TEST_F(InventoryTest, CombineSwordAndPoisonFlower) {
    Item sword("sword", "Sword", "A sharp blade");
    Item flower("poison_flower", "Poison Flower", "A deadly flower");

    inventory->addItem(sword);
    inventory->addItem(flower);

    std::string result = inventory->processCombinations();

    // Should have combined into poison sword
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(inventory->hasItem("poison_sword"));
    EXPECT_FALSE(inventory->hasItem("sword"));
    EXPECT_FALSE(inventory->hasItem("poison_flower"));
    EXPECT_EQ(inventory->getItemCount(), 1);
}

TEST_F(InventoryTest, CombinationRequiresBothItems) {
    Item sword("sword", "Sword", "A sharp blade");
    inventory->addItem(sword);

    std::string result = inventory->processCombinations();

    // Should not combine with only sword
    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(inventory->hasItem("sword"));
    EXPECT_FALSE(inventory->hasItem("poison_sword"));
}

TEST_F(InventoryTest, NoCombinationWithoutCorrectItems) {
    Item key("key", "Key", "An old key");
    Item book("book", "Book", "A dusty book");

    inventory->addItem(key);
    inventory->addItem(book);

    std::string result = inventory->processCombinations();

    // Should not combine random items
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(inventory->getItemCount(), 2);
}

TEST_F(InventoryTest, PoisonSwordHasCorrectProperties) {
    Item sword("sword", "Sword", "A sharp blade");
    Item flower("poison_flower", "Poison Flower", "A deadly flower");

    inventory->addItem(sword);
    inventory->addItem(flower);
    inventory->processCombinations();

    Item& poisonSword = inventory->getItem("poison_sword");
    EXPECT_EQ(poisonSword.getId(), "poison_sword");
    EXPECT_EQ(poisonSword.getName(), "Poison Sword");
}

TEST_F(InventoryTest, MultipleCombinationAttempts) {
    Item sword("sword", "Sword", "A sharp blade");
    Item flower("poison_flower", "Poison Flower", "A deadly flower");

    inventory->addItem(sword);
    inventory->addItem(flower);

    // First combination should work
    std::string result1 = inventory->processCombinations();
    EXPECT_FALSE(result1.empty());
    EXPECT_TRUE(inventory->hasItem("poison_sword"));

    // Second attempt should do nothing
    std::string result2 = inventory->processCombinations();
    EXPECT_TRUE(result2.empty());
}
