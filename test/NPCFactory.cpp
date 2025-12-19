#include <gtest/gtest.h>
#include "NPCFactory.hpp"
#include "Guard.hpp"
#include "Prisoner.hpp"
#include "Knight.hpp"
#include "King.hpp"

// Test the NPCFactory
class NPCFactoryTest : public ::testing::Test {
 protected:
    NPCFactory factory;
};

// Test creating different NPC types
TEST_F(NPCFactoryTest, CreateGuard) {
    NPC* npc = factory.createNPC("Guard");
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "Guard");
    delete npc;
}

// Test creating different NPC types
TEST_F(NPCFactoryTest, CreatePrisoner) {
    NPC* npc = factory.createNPC("Prisoner");
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "Prisoner");
    delete npc;
}

// Test creating different NPC types
TEST_F(NPCFactoryTest, CreateKnight) {
    NPC* npc = factory.createNPC("Knight");
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "Knight");
    delete npc;
}

// Test creating different NPC types
TEST_F(NPCFactoryTest, CreateKing) {
    NPC* npc = factory.createNPC("King");
    EXPECT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "King");
    delete npc;
}

// Test creating an invalid NPC type
TEST_F(NPCFactoryTest, InvalidTypeReturnsNullptr) {
    NPC* npc = factory.createNPC("InvalidNPC");
    EXPECT_EQ(npc, nullptr);
}
