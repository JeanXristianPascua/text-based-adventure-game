#include "gtest/gtest.h"
#include "Environment.hpp"
#include "Room.hpp"
#include "Direction.hpp"
#include "Exit.hpp"
#include "WorldObjectFactory.hpp"
#include "NPCFactory.hpp"

// Small concrete Environment for testing base-class behavior
class TestEnvironment : public Environment {
 public:
    explicit TestEnvironment(const std::string& description)
            : Environment(description) {}
    void generateRooms() override {}
};

// Test fixture for Environment base class
class EnvironmentTest : public ::testing::Test {
 protected:
    Environment* env;
    void SetUp() override {
    env = new TestEnvironment("Test environment");
    }
    void TearDown() override {
    delete env;
    }
};

// Test fixture for CastleMain
class CastleMainTest : public ::testing::Test {
 protected:
    CastleMain* castleMain;
    void SetUp() override {
    castleMain = new CastleMain();
    castleMain->generateRooms();
    }
    void TearDown() override {
    delete castleMain;
    }
};

// Test fixture for CastleDungeon
class CastleDungeonTest : public ::testing::Test {
 protected:
    CastleDungeon* castleDungeon;
    void SetUp() override {
    castleDungeon = new CastleDungeon();
    castleDungeon->generateRooms();
    }
    void TearDown() override {
    delete castleDungeon;
    }
};

// Test fixture for CastleCourtyard
class CastleCourtyardTest : public ::testing::Test {
 protected:
    CastleCourtyard* castleCourtyard;
    void SetUp() override {
    castleCourtyard = new CastleCourtyard();
    castleCourtyard->generateRooms();
    }
    void TearDown() override {
    delete castleCourtyard;
    }
};

//Environment Base Class Tests

TEST_F(EnvironmentTest, ConstructorSetsDescription) {
    TestEnvironment testEnv("Custom description");
    EXPECT_EQ(testEnv.getDescription(), "Custom description");
}

TEST_F(EnvironmentTest, AddRoomSuccess) {
    Room* room = new Room("TestRoom", "A test room");
    env->addRoom(room);
    Room* retrieved = env->getRoomByName("TestRoom");
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getName(), "TestRoom");
}

TEST_F(EnvironmentTest, AddNullRoomDoesNotCrash) {
    EXPECT_NO_THROW(env->addRoom(nullptr));
    // Verify no rooms were added
    Room* retrieved = env->getRoomByName("NonExistent");
    EXPECT_EQ(retrieved, nullptr);
}

TEST_F(EnvironmentTest, GetRoomByNameReturnsNullForNonExistent) {
    Room* result = env->getRoomByName("NonExistentRoom");
    EXPECT_EQ(result, nullptr);
}

TEST_F(EnvironmentTest, GetRoomByNameFindsCorrectRoom) {
    Room* room1 = new Room("Room1", "First room");
    Room* room2 = new Room("Room2", "Second room");
    Room* room3 = new Room("Room3", "Third room");
    env->addRoom(room1);
    env->addRoom(room2);
    env->addRoom(room3);
    Room* found = env->getRoomByName("Room2");
    EXPECT_EQ(found, room2);
    EXPECT_EQ(found->getName(), "Room2");
}

TEST_F(EnvironmentTest, DestructorCleansUpRooms) {
    Room* room1 = new Room("Room1", "First room");
    Room* room2 = new Room("Room2", "Second room");
    env->addRoom(room1);
    env->addRoom(room2);
    EXPECT_NO_THROW(delete env);
    env = nullptr;
}

//CastleMain Tests

TEST_F(CastleMainTest, ConstructorSetsCorrectDescription) {
    EXPECT_EQ(castleMain->getDescription(),
    "The main castle halls and chambers");
}

TEST_F(CastleMainTest, GeneratesAllFiveRooms) {
    EXPECT_NE(castleMain->getRoomByName("Library"), nullptr);
    EXPECT_NE(castleMain->getRoomByName("Courtyard"), nullptr);
    EXPECT_NE(castleMain->getRoomByName("Armory"), nullptr);
    EXPECT_NE(castleMain->getRoomByName("Throne Room"), nullptr);
    EXPECT_NE(castleMain->getRoomByName("Secret Chamber"), nullptr);
}

TEST_F(CastleMainTest, LibraryHasCorrectWorldObjects) {
    Room* library = castleMain->getRoomByName("Library");
    ASSERT_NE(library, nullptr);
    // Should have BookPile and MysteriousBook
    auto objects = library->getWorldObjects();
    EXPECT_GE(objects.size(), 2);
}

TEST_F(CastleMainTest, CourtyardHasGuardNPC) {
    Room* courtyard = castleMain->getRoomByName("Courtyard");
    ASSERT_NE(courtyard, nullptr);
    auto objects = courtyard->getWorldObjects();
    EXPECT_GE(objects.size(), 1);
}

TEST_F(CastleMainTest, ArmoryHasKnightNPC) {
    Room* armory = castleMain->getRoomByName("Armory");
    ASSERT_NE(armory, nullptr);
    auto objects = armory->getWorldObjects();
    EXPECT_GE(objects.size(), 1);
}

TEST_F(CastleMainTest, ThroneRoomHasKingNPC) {
    Room* throneRoom = castleMain->getRoomByName("Throne Room");
    ASSERT_NE(throneRoom, nullptr);
    auto objects = throneRoom->getWorldObjects();
    EXPECT_GE(objects.size(), 1);
}

TEST_F(CastleMainTest, LibraryExitsAreCorrect) {
    Room* library = castleMain->getRoomByName("Library");
    ASSERT_NE(library, nullptr);
    EXPECT_NE(library->getExit(Direction::NORTH), nullptr);  // to Armory
    EXPECT_NE(library->getExit(Direction::EAST), nullptr);   // to Courtyard
    EXPECT_EQ(library->getExit(Direction::SOUTH), nullptr);
    EXPECT_EQ(library->getExit(Direction::WEST), nullptr);
}

TEST_F(CastleMainTest, CourtyardExitsAreCorrect) {
    Room* courtyard = castleMain->getRoomByName("Courtyard");
    ASSERT_NE(courtyard, nullptr);
    EXPECT_NE(courtyard->getExit(Direction::WEST), nullptr);  // to Library
    EXPECT_NE(courtyard->getExit(Direction::NORTH), nullptr); // to Throne Room
    EXPECT_EQ(courtyard->getExit(Direction::SOUTH), nullptr);
    EXPECT_EQ(courtyard->getExit(Direction::EAST), nullptr);
}

TEST_F(CastleMainTest, ArmoryExitsAreCorrect) {
    Room* armory = castleMain->getRoomByName("Armory");
    ASSERT_NE(armory, nullptr);
    EXPECT_NE(armory->getExit(Direction::SOUTH), nullptr);   // to Library
    EXPECT_EQ(armory->getExit(Direction::NORTH), nullptr);
    EXPECT_EQ(armory->getExit(Direction::EAST), nullptr);
    EXPECT_EQ(armory->getExit(Direction::WEST), nullptr);
}

TEST_F(CastleMainTest, ThroneRoomExitsAreCorrect) {
    Room* throneRoom = castleMain->getRoomByName("Throne Room");
    ASSERT_NE(throneRoom, nullptr);
    EXPECT_NE(throneRoom->getExit(Direction::WEST), nullptr);  // to Armory
    EXPECT_NE(throneRoom->getExit(Direction::SOUTH), nullptr); // to Courtyard
    EXPECT_NE(throneRoom->getExit(Direction::EAST), nullptr);
    EXPECT_EQ(throneRoom->getExit(Direction::NORTH), nullptr);
}

TEST_F(CastleMainTest, SecretChamberExitIsCorrect) {
    Room* secretChamber = castleMain->getRoomByName("Secret Chamber");
    ASSERT_NE(secretChamber, nullptr);
    EXPECT_NE(secretChamber->getExit(Direction::WEST), nullptr);
    EXPECT_EQ(secretChamber->getExit(Direction::NORTH), nullptr);
    EXPECT_EQ(secretChamber->getExit(Direction::SOUTH), nullptr);
    EXPECT_EQ(secretChamber->getExit(Direction::EAST), nullptr);
}

TEST_F(CastleMainTest, SecretChamberExitIsLocked) {
    Room* throneRoom = castleMain->getRoomByName("Throne Room");
    ASSERT_NE(throneRoom, nullptr);
    Exit* exitToSecret = throneRoom->getExit(Direction::EAST);
    ASSERT_NE(exitToSecret, nullptr);
    EXPECT_TRUE(exitToSecret->getIsLocked());
}

TEST_F(CastleMainTest, RoomNavigationIsSymmetric) {
    Room* library = castleMain->getRoomByName("Library");
    Room* courtyard = castleMain->getRoomByName("Courtyard");
    // Library EAST -> Courtyard
    Exit* libraryEast = library->getExit(Direction::EAST);
    ASSERT_NE(libraryEast, nullptr);
    EXPECT_EQ(libraryEast->getDestination(), courtyard);
    // Courtyard WEST -> Library
    Exit* courtyardWest = courtyard->getExit(Direction::WEST);
    ASSERT_NE(courtyardWest, nullptr);
    EXPECT_EQ(courtyardWest->getDestination(), library);
}

//CastleDungeon Tests

TEST_F(CastleDungeonTest, ConstructorSetsCorrectDescription) {
    EXPECT_EQ(castleDungeon->getDescription(),
    "The dark dungeons beneath the castle");
}

TEST_F(CastleDungeonTest, GeneratesPrisonRoom) {
    Room* prison = castleDungeon->getRoomByName("Prison");
    EXPECT_NE(prison, nullptr);
}

TEST_F(CastleDungeonTest, PrisonHasPrisonerNPC) {
    Room* prison = castleDungeon->getRoomByName("Prison");
    ASSERT_NE(prison, nullptr);
    auto objects = prison->getWorldObjects();
    EXPECT_GE(objects.size(), 1);
}

TEST_F(CastleDungeonTest, PrisonHasCorrectDescription) {
    Room* prison = castleDungeon->getRoomByName("Prison");
    ASSERT_NE(prison, nullptr);
    std::string desc = prison->getDescription();
    EXPECT_TRUE(desc.find("iron-barred cells") != std::string::npos);
}

//CastleCourtyard Tests

TEST_F(CastleCourtyardTest, ConstructorSetsCorrectDescription) {
    EXPECT_EQ(castleCourtyard->getDescription(),
    "The outer courtyard and gardens");
}

TEST_F(CastleCourtyardTest, GeneratesAllThreeRooms) {
    EXPECT_NE(castleCourtyard->getRoomByName("Garden"), nullptr);
    EXPECT_NE(castleCourtyard->getRoomByName("Main Gate"), nullptr);
    EXPECT_NE(castleCourtyard->getRoomByName("Stables"), nullptr);
}

TEST_F(CastleCourtyardTest, GardenHasFountainWorldObject) {
    Room* garden = castleCourtyard->getRoomByName("Garden");
    ASSERT_NE(garden, nullptr);
    auto objects = garden->getWorldObjects();
    EXPECT_GE(objects.size(), 1);
}

TEST_F(CastleCourtyardTest, StablesHasHorseWorldObject) {
    Room* stables = castleCourtyard->getRoomByName("Stables");
    ASSERT_NE(stables, nullptr);
    auto objects = stables->getWorldObjects();
    EXPECT_GE(objects.size(), 1);
}

TEST_F(CastleCourtyardTest, GardenExitsAreCorrect) {
    Room* garden = castleCourtyard->getRoomByName("Garden");
    ASSERT_NE(garden, nullptr);
    EXPECT_NE(garden->getExit(Direction::EAST), nullptr);  // to Main Gate
    EXPECT_EQ(garden->getExit(Direction::NORTH), nullptr);
    EXPECT_EQ(garden->getExit(Direction::SOUTH), nullptr);
    EXPECT_EQ(garden->getExit(Direction::WEST), nullptr);
}

TEST_F(CastleCourtyardTest, MainGateExitsAreCorrect) {
    Room* mainGate = castleCourtyard->getRoomByName("Main Gate");
    ASSERT_NE(mainGate, nullptr);
    EXPECT_NE(mainGate->getExit(Direction::WEST), nullptr);  // to Garden
    EXPECT_NE(mainGate->getExit(Direction::EAST), nullptr);  // to Stables
    EXPECT_EQ(mainGate->getExit(Direction::NORTH), nullptr);
    EXPECT_EQ(mainGate->getExit(Direction::SOUTH), nullptr);
}

TEST_F(CastleCourtyardTest, StablesExitsAreCorrect) {
    Room* stables = castleCourtyard->getRoomByName("Stables");
    ASSERT_NE(stables, nullptr);
    EXPECT_NE(stables->getExit(Direction::WEST), nullptr);  // to Main Gate
    EXPECT_EQ(stables->getExit(Direction::NORTH), nullptr);
    EXPECT_EQ(stables->getExit(Direction::SOUTH), nullptr);
    EXPECT_EQ(stables->getExit(Direction::EAST), nullptr);
}

TEST_F(CastleCourtyardTest, NavigationIsSymmetric) {
    Room* garden = castleCourtyard->getRoomByName("Garden");
    Room* mainGate = castleCourtyard->getRoomByName("Main Gate");
    Room* stables = castleCourtyard->getRoomByName("Stables");
    // Garden EAST -> Main Gate, Main Gate WEST -> Garden
    Exit* gardenEast = garden->getExit(Direction::EAST);
    ASSERT_NE(gardenEast, nullptr);
    EXPECT_EQ(gardenEast->getDestination(), mainGate);
    Exit* mainGateWest = mainGate->getExit(Direction::WEST);
    ASSERT_NE(mainGateWest, nullptr);
    EXPECT_EQ(mainGateWest->getDestination(), garden);
    // Main Gate EAST -> Stables, Stables WEST -> Main Gate
    Exit* mainGateEast = mainGate->getExit(Direction::EAST);
    ASSERT_NE(mainGateEast, nullptr);
    EXPECT_EQ(mainGateEast->getDestination(), stables);
    Exit* stablesWest = stables->getExit(Direction::WEST);
    ASSERT_NE(stablesWest, nullptr);
    EXPECT_EQ(stablesWest->getDestination(), mainGate);
}

// ============= Integration Tests =============

TEST(EnvironmentIntegrationTest, MultipleEnvironmentsCanCoexist) {
    CastleMain* main = new CastleMain();
    CastleDungeon* dungeon = new CastleDungeon();
    CastleCourtyard* courtyard = new CastleCourtyard();
    main->generateRooms();
    dungeon->generateRooms();
    courtyard->generateRooms();
    // Verify each environment has its own rooms
    EXPECT_NE(main->getRoomByName("Library"), nullptr);
    EXPECT_EQ(dungeon->getRoomByName("Library"), nullptr);
    EXPECT_EQ(courtyard->getRoomByName("Library"), nullptr);
    EXPECT_NE(dungeon->getRoomByName("Prison"), nullptr);
    EXPECT_EQ(main->getRoomByName("Prison"), nullptr);
    EXPECT_EQ(courtyard->getRoomByName("Prison"), nullptr);
    EXPECT_NE(courtyard->getRoomByName("Main Gate"), nullptr);
    EXPECT_EQ(main->getRoomByName("Main Gate"), nullptr);
    EXPECT_EQ(dungeon->getRoomByName("Main Gate"), nullptr);
    delete main;
    delete dungeon;
    delete courtyard;
}

TEST(EnvironmentIntegrationTest, GenerateRoomsCanBeCalledMultipleTimes) {
    CastleMain* castle = new CastleMain();
    castle->generateRooms();
    Room* library1 = castle->getRoomByName("Library");
    castle->generateRooms();
    Room* library2 = castle->getRoomByName("Library");
    // Second generation should create new rooms
    EXPECT_NE(library1, nullptr);
    EXPECT_NE(library2, nullptr);
    delete castle;
}
