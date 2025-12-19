#include "gtest/gtest.h"
#include "Exit.hpp"
#include "Room.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include "Direction.hpp"
#include "Inventory.hpp"

// Test fixture for Exit tests
class ExitTest : public ::testing::Test {
 protected:
    Room* room1;
    Room* room2;
    Player* player;

    void SetUp() override {
        room1 = new Room("Room 1", "First room");
        room2 = new Room("Room 2", "Second room");
        player = new Player();
        player->setCurrentRoom(room1);
    }

    void TearDown() override {
        delete room1;
        delete room2;
        delete player;
    }
};

// Basic exit tests

TEST_F(ExitTest, UnlockedExitAllowsPassage) {
    Exit* exit = new Exit(room2, Direction::NORTH, false);

    EXPECT_TRUE(exit->canPass(*player));
    EXPECT_FALSE(exit->getIsLocked());

    delete exit;
}

TEST_F(ExitTest, LockedExitBlocksPassage) {
    Exit* exit = new Exit(room2, Direction::NORTH, true, "key");

    EXPECT_FALSE(exit->canPass(*player));
    EXPECT_TRUE(exit->getIsLocked());

    delete exit;
}

TEST_F(ExitTest, ExitDestination) {
    Exit* exit = new Exit(room2, Direction::NORTH);

    EXPECT_EQ(exit->getDestination(), room2);

    delete exit;
}

// Unlocking tests

TEST_F(ExitTest, UnlockWithCorrectKey) {
    Exit* exit = new Exit(room2, Direction::NORTH, true, "prison_key");
    Item key("prison_key", "Prison Key", "An old iron key");

    EXPECT_TRUE(exit->getIsLocked());
    EXPECT_TRUE(exit->unlock(key));
    EXPECT_FALSE(exit->getIsLocked());

    delete exit;
}

TEST_F(ExitTest, UnlockWithWrongKey) {
    Exit* exit = new Exit(room2, Direction::NORTH, true, "prison_key");
    Item wrongKey("castle_key", "Castle Key", "A different key");

    EXPECT_TRUE(exit->getIsLocked());
    EXPECT_FALSE(exit->unlock(wrongKey));
    EXPECT_TRUE(exit->getIsLocked());  // Should still be locked

    delete exit;
}

TEST_F(ExitTest, UnlockAlreadyUnlockedExit) {
    Exit* exit = new Exit(room2, Direction::NORTH, false);
    Item key("any_key", "Any Key", "Some key");

    EXPECT_FALSE(exit->getIsLocked());
    EXPECT_FALSE(exit->unlock(key));  // Returns false - already unlocked

    delete exit;
}

TEST_F(ExitTest, CanPassAfterUnlocking) {
    Exit* exit = new Exit(room2, Direction::NORTH, true, "key");
    Item key("key", "Key", "A key");

    EXPECT_FALSE(exit->canPass(*player));  // Locked, can't pass

    exit->unlock(key);

    EXPECT_TRUE(exit->canPass(*player));  // Unlocked, can pass

    delete exit;
}

// Multiple unlocks

TEST_F(ExitTest, MultipleWrongKeysThenCorrectKey) {
    Exit* exit = new Exit(room2, Direction::NORTH, true, "correct_key");
    Item wrongKey1("wrong1", "Wrong Key 1", "A key");
    Item wrongKey2("wrong2", "Wrong Key 2", "Another key");
    Item correctKey("correct_key", "Correct Key", "The right key");

    EXPECT_FALSE(exit->unlock(wrongKey1));
    EXPECT_TRUE(exit->getIsLocked());

    EXPECT_FALSE(exit->unlock(wrongKey2));
    EXPECT_TRUE(exit->getIsLocked());

    EXPECT_TRUE(exit->unlock(correctKey));
    EXPECT_FALSE(exit->getIsLocked());

    delete exit;
}

TEST_F(ExitTest, UnlockTwiceWithSameKey) {
    Exit* exit = new Exit(room2, Direction::NORTH, true, "key");
    Item key("key", "Key", "A key");

    EXPECT_TRUE(exit->unlock(key));  // First unlock succeeds
    EXPECT_FALSE(exit->getIsLocked());

    EXPECT_FALSE(exit->unlock(key));  // Second unlock fails (already unlocked)

    delete exit;
}

// Exits without required keys

TEST_F(ExitTest, LockedExitWithoutRequiredKeyId) {
    Exit* exit = new Exit(room2, Direction::NORTH, true, "");

    EXPECT_TRUE(exit->getIsLocked());
    EXPECT_FALSE(exit->canPass(*player));

    delete exit;
}

TEST_F(ExitTest, UnlockExitWithoutRequiredKeyId) {
    Exit* exit = new Exit(room2, Direction::NORTH, true, "");
    Item anyKey("any_key", "Any Key", "Some key");

    // No required key ID, so no key can unlock it
    EXPECT_FALSE(exit->unlock(anyKey));
    EXPECT_TRUE(exit->getIsLocked());

    delete exit;
}

// Game specific tests

TEST_F(ExitTest, PrisonKeyUnlocksPrisonDoor) {
    Exit* prisonExit = new Exit(room2, Direction::EAST, true, "prison_key",
                                "A heavy iron door");
    Item prisonKey("prison_key", "Prison Key",
                   "An old iron key with rust spots");

    EXPECT_TRUE(prisonExit->getIsLocked());
    EXPECT_TRUE(prisonExit->unlock(prisonKey));
    EXPECT_FALSE(prisonExit->getIsLocked());

    delete prisonExit;
}

TEST_F(ExitTest, PoisonSwordUnlocksSecretChamber) {
    Exit* secretExit = new Exit(room2, Direction::EAST, true, "poison_sword",
                                "The King won't let you past..");
    Item poisonSword("poison_sword", "Poison Sword",
                     "A deadly blade coated with poison");

    EXPECT_TRUE(secretExit->getIsLocked());
    EXPECT_TRUE(secretExit->unlock(poisonSword));
    EXPECT_FALSE(secretExit->getIsLocked());

    delete secretExit;
}

TEST_F(ExitTest, RegularSwordCannotUnlockSecretChamber) {
    Exit* secretExit = new Exit(room2, Direction::EAST, true, "poison_sword");
    Item regularSword("sword", "Sword", "A regular blade");

    EXPECT_FALSE(secretExit->unlock(regularSword));
    EXPECT_TRUE(secretExit->getIsLocked());

    delete secretExit;
}

// Integration tests

TEST_F(ExitTest, PlayerWithKeyInInventory) {
    Exit* exit = new Exit(room2, Direction::NORTH, true, "key");
    Item key("key", "Key", "A key");

    // Add key to player's inventory
    player->getInventory()->addItem(key);

    // Player can't pass locked door
    EXPECT_FALSE(exit->canPass(*player));

    // Unlock with item from inventory
    Item& keyFromInv = player->getInventory()->getItem("key");
    EXPECT_TRUE(exit->unlock(keyFromInv));

    // Now player can pass
    EXPECT_TRUE(exit->canPass(*player));

    delete exit;
}

TEST_F(ExitTest, FullUnlockSequence) {
    // Create locked exit
    Exit* exit = new Exit(room2, Direction::NORTH, true, "prison_key");

    // Player tries to pass - blocked
    EXPECT_FALSE(exit->canPass(*player));

    // Player finds and picks up key
    Item* key = new Item("prison_key", "Prison Key", "An old key");
    room1->addItem(key);
    player->pickUpItem("Prison Key");

    // Player uses key
    Item& keyFromInv = player->getInventory()->getItem("prison_key");
    EXPECT_TRUE(exit->unlock(keyFromInv));

    // Player can now pass
    EXPECT_TRUE(exit->canPass(*player));

    delete exit;
}
