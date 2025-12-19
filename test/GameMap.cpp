#include "gtest/gtest.h"

#include "GameMap.hpp"
#include "Room.hpp"
#include "Exit.hpp"
#include "Direction.hpp"

TEST(GameMapTest, GenerateWorldCreatesKeyRooms) {
  GameMap gm;
  gm.generateWorld();

  // Key rooms in each environment should exist
  EXPECT_NE(gm.getRoomByName("Library"), nullptr);
  EXPECT_NE(gm.getRoomByName("Prison"), nullptr);
  EXPECT_NE(gm.getRoomByName("Main Gate"), nullptr);
}

TEST(GameMapTest, StartingRoomIsMainGate) {
  GameMap gm;
  gm.generateWorld();

  Room* start = gm.getStartingRoom();
  ASSERT_NE(start, nullptr);
  EXPECT_EQ(start->getName(), "Main Gate");
}

TEST(GameMapTest, ConnectsMainGateToCourtyard) {
  GameMap gm;
  gm.generateWorld();

  Room* mainGate = gm.getRoomByName("Main Gate");
  Room* courtyard = gm.getRoomByName("Courtyard");

  ASSERT_NE(mainGate, nullptr);
  ASSERT_NE(courtyard, nullptr);

  Exit* north = mainGate->getExit(Direction::NORTH);
  ASSERT_NE(north, nullptr);
  EXPECT_EQ(north->getDestination(), courtyard);

  Exit* south = courtyard->getExit(Direction::SOUTH);
  ASSERT_NE(south, nullptr);
  EXPECT_EQ(south->getDestination(), mainGate);
}

TEST(GameMapTest, CourtyardToPrisonIsLocked) {
  GameMap gm;
  gm.generateWorld();

  Room* courtyard = gm.getRoomByName("Courtyard");
  Room* prison = gm.getRoomByName("Prison");

  ASSERT_NE(courtyard, nullptr);
  ASSERT_NE(prison, nullptr);

  Exit* east = courtyard->getExit(Direction::EAST);
  ASSERT_NE(east, nullptr);
  EXPECT_EQ(east->getDestination(), prison);
  EXPECT_TRUE(east->getIsLocked());

  Exit* west = prison->getExit(Direction::WEST);
  ASSERT_NE(west, nullptr);
  EXPECT_EQ(west->getDestination(), courtyard);
}
