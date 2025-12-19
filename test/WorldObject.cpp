#include <gtest/gtest.h>
#include "WorldObject.hpp"
#include "Player.hpp"

// Mock WorldObject class for testing
class MockWorldObject : public WorldObject {
 public:
    MockWorldObject(const std::string& name, const std::string& description)
        : WorldObject(name, description) {}

    std::string interact(const Player& player) override {
        return "Mock interaction with " + getName();
    }
};

// Test class for WorldObject functionality
class WorldObjectTest : public ::testing::Test {
 protected:
    MockWorldObject* mockObject;
    Player* player;

    void SetUp() override {
        mockObject = new MockWorldObject("Test Object",
            "A test object description");
        player = new Player();
    }

    void TearDown() override {
        delete mockObject;
        delete player;
    }
};

// Test for WorldObject's name and description
TEST_F(WorldObjectTest, GetNameAndDescription) {
    EXPECT_EQ(mockObject->getName(), "Test Object");
    EXPECT_EQ(mockObject->getDescription(), "A test object description");
}
