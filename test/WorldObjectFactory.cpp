#include <gtest/gtest.h>
#include "WorldObjectFactory.hpp"
#include "Fountain.hpp"
#include "Horse.hpp"
#include "MysteriousBook.hpp"
#include "BookPile.hpp"

// Test the WorldObjectFactory
class WorldObjectFactoryTest : public ::testing::Test {
 protected:
    WorldObjectFactory factory;
};

// Test creating different WorldObject types
TEST_F(WorldObjectFactoryTest, CreateFountain) {
    WorldObject* object = factory.createWorldObject("Fountain");
    EXPECT_NE(object, nullptr);
    EXPECT_EQ(object->getName(), "Fountain");
    delete object;
}

// Test creating different WorldObject types
TEST_F(WorldObjectFactoryTest, CreateHorse) {
    WorldObject* object = factory.createWorldObject("Horse");
    EXPECT_NE(object, nullptr);
    EXPECT_EQ(object->getName(), "Horse");
    delete object;
}

// Test creating different WorldObject types
TEST_F(WorldObjectFactoryTest, InvalidTypeReturnsNullptr) {
    WorldObject* object = factory.createWorldObject("InvalidObject");
    EXPECT_EQ(object, nullptr);
}
