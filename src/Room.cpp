#include "Room.hpp"

#include <algorithm>
#include <iostream>
#include <string>

#include "Exit.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "WorldObject.hpp"
#include "StringUtils.hpp"
#include "RoomFormatter.hpp"

// Constructor to initialize room with name and description
Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description) {}

// Destructor to clean up dynamically allocated memory
Room::~Room() {
    // Clean up exits
    for (const auto& pair : exits) {
        delete pair.second;
    }

    // Clean up items
    for (Item* item : items) {
        delete item;
    }

    // Clean up world objects
    for (WorldObject* obj : worldObjects) {
        delete obj;
    }
}

// Method to handle player entering the room
void Room::enter(const Player& player) {
    // Display entry message, not full examination
    std::cout << RoomFormatter::formatEntry(this) << std::endl;
}

Exit* Room::getExit(Direction direction) {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return nullptr;
}

void Room::addExit(Direction direction, Room* destination, Exit* exit) {
    if (exit) {
        exits[direction] = exit;
    } else {
        exits[direction] = new Exit(destination, direction);
    }
}

void Room::addItem(Item* item) {
    if (item) {
        items.push_back(item);
    }
}

Item* Room::removeItem(const std::string& itemName) {
    // First try exact match (case-insensitive)
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (StringUtils::equalsIgnoreCase((*it)->getName(), itemName)) {
            Item* item = *it;
            items.erase(it);
            return item;
        }
    }

    // Then try partial match (substring search)
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (StringUtils::containsIgnoreCase((*it)->getName(), itemName)) {
            Item* item = *it;
            items.erase(it);
            return item;
        }
    }
    return nullptr;
}

void Room::addWorldObject(WorldObject* object) {
    if (object) {
        worldObjects.push_back(object);
    }
}

WorldObject* Room::getWorldObjectByName(const std::string& objectName) {
    // First try exact match
    for (WorldObject* object : worldObjects) {
        if (StringUtils::equalsIgnoreCase(object->getName(), objectName)) {
            return object;
        }
    }

    // Then try partial match
    for (WorldObject* object : worldObjects) {
        if (StringUtils::containsIgnoreCase(object->getName(), objectName)) {
            return object;
        }
    }
    return nullptr;
}
