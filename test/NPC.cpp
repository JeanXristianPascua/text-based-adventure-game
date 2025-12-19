#include <gtest/gtest.h>
#include "NPC.hpp"
#include "Item.hpp"
#include "Player.hpp"

// Test class for NPC functionality
class NPCTest : public ::testing::Test {
 protected:
    NPC* npc;

    void SetUp() override {
        npc = new NPC("Guard", "A formidable guard who protects the kingdom.");
    }

    void TearDown() override {
        delete npc;
    }
};

// Test NPC constructor
TEST_F(NPCTest, AddItemToInventory) {
    Item sword("sword", "A sharp steel sword", "Used for combat.");
    EXPECT_TRUE(npc->addItem(sword));
}

// Test NPC hasItem method
TEST_F(NPCTest, HasItemInInventory) {
    Item sword("sword", "A sharp steel sword", "Used for combat.");
    npc->addItem(sword);

    EXPECT_TRUE(npc->hasItem("sword"));
    EXPECT_FALSE(npc->hasItem("shield"));
}

// Test NPC removeItem method
TEST_F(NPCTest, RemoveItemFromInventory) {
    Item sword("sword", "A sharp steel sword", "Used for combat.");
    npc->addItem(sword);

    EXPECT_TRUE(npc->removeItem("sword"));
    EXPECT_FALSE(npc->hasItem("sword"));
}

// Test NPC interact method
TEST_F(NPCTest, InteractWithPlayer) {
    Player player;

    std::string interaction = npc->interact(player);
    EXPECT_EQ(interaction, "Looks at you with curiosity.");
}
