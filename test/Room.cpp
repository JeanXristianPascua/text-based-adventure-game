#include "gtest/gtest.h"

#include "Room.hpp"
#include "Item.hpp"
#include "WorldObject.hpp"
#include "Player.hpp"
#include "Direction.hpp"
#include "Exit.hpp"

// Small concrete WorldObject for testing
class TestWorldObject : public WorldObject {
 public:
  TestWorldObject(const std::string& name, const std::string& desc)
      : WorldObject(name, desc) {}
  std::string interact(const Player& player) override { return "noop"; }
};

TEST(RoomTest, AddExitAndGetDestination) {
  Room* a = new Room("A", "Room A");
  Room* b = new Room("B", "Room B");

  a->addExit(Direction::NORTH, b);
  Exit* e = a->getExit(Direction::NORTH);
  ASSERT_NE(e, nullptr);
  EXPECT_EQ(e->getDestination(), b);
  EXPECT_FALSE(e->getIsLocked());

  delete a;
  delete b;
}

TEST(RoomTest, AddAndRemoveItemExactAndCaseInsensitive) {
  Room room("Test", "Test room");

  Item* sword = new Item("s1", "Rusty Sword", "An old sword");
  room.addItem(sword);

  Item* removed = room.removeItem("rusty sword");
  ASSERT_NE(removed, nullptr);
  EXPECT_EQ(removed->getName(), "Rusty Sword");
  delete removed;  // room no longer owns it

  // Removing again should fail
  EXPECT_EQ(room.removeItem("Rusty Sword"), nullptr);
}

TEST(RoomTest, RemoveItemPartialMatch) {
  Room room("Test", "Test room");
  Item* scroll = new Item("i1", "Ancient Scroll", "Old parchment");
  room.addItem(scroll);

  Item* removed = room.removeItem("scroll");
  ASSERT_NE(removed, nullptr);
  EXPECT_EQ(removed->getName(), "Ancient Scroll");
  delete removed;
}

TEST(RoomTest, RemoveNonexistentItemReturnsNull) {
  Room room("Empty", "No items here");
  EXPECT_EQ(room.removeItem("nothing"), nullptr);
}

TEST(RoomTest, WorldObjectAddAndLookup) {
  Room room("ObjRoom", "Has objects");
  TestWorldObject* to = new TestWorldObject("Statue", "A stone statue");
  room.addWorldObject(to);

  WorldObject* found = room.getWorldObjectByName("statue");
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->getName(), "Statue");

  WorldObject* partial = room.getWorldObjectByName("stat");
  ASSERT_NE(partial, nullptr);
  EXPECT_EQ(partial->getName(), "Statue");
}

TEST(RoomTest, EnterPrintsEntry) {
  Room room("Hall", "A long hall");
  Player p;

  testing::internal::CaptureStdout();
  room.enter(p);
  std::string output = testing::internal::GetCapturedStdout();

  // Output should contain room name and description
  EXPECT_NE(output.find("Hall"), std::string::npos);
  EXPECT_NE(output.find("A long hall"), std::string::npos);
}
