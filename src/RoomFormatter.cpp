#include <map>
#include <vector>
#include <string>
#include "RoomFormatter.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "WorldObject.hpp"
#include "Exit.hpp"
#include "Direction.hpp"

std::string RoomFormatter::formatRoom(const Room* room) {
    if (!room) {
        return MessageFormatter::youAreNowhere();
    }

    std::string result = MessageFormatter::roomHeader(room->getName());
    result += room->getDescription() + "\n";

    // Add items if any
    std::vector<Item*> items = room->getItems();
    if (!items.empty()) {
        result += formatItemsList(items);
    }

    // Add world objects if any
    std::vector<WorldObject*> objects = room->getWorldObjects();
    if (!objects.empty()) {
        result += formatWorldObjectsList(objects);
    }

    // Add exits if any
    std::map<Direction, Exit*> exits = room->getExits();
    if (!exits.empty()) {
        result += formatExitsList(exits);
    }

    return result;
}

std::string RoomFormatter::formatEntry(const Room* room) {
    if (!room) {
        return "";
    }

    return MessageFormatter::roomHeader(room->getName()) +
           room->getDescription();
}

std::string RoomFormatter::formatItemsList(const std::vector<Item*>& items) {
    std::string result = MessageFormatter::itemsListHeader();

    result = std::accumulate(
        items.begin(),
        items.end(),
        result,
        [](const std::string& acc, const Item* item) {
            return acc + MessageFormatter::itemEntry(item->getName());
        });

    return result;
}

std::string RoomFormatter::formatWorldObjectsList(
    const std::vector<WorldObject*>& objects) {
    std::string result = MessageFormatter::worldObjectsListHeader();

    result = std::accumulate(
        objects.begin(),
        objects.end(),
        result,
        [](const std::string& acc, const WorldObject* obj) {
            return acc + MessageFormatter::worldObjectEntry(
                obj->getName(), obj->getDescription());
        });

    return result;
}

std::string RoomFormatter::formatExitsList(
    const std::map<Direction, Exit*>& exits) {
    std::string result = MessageFormatter::exitsListHeader();

    for (const auto& pair : exits) {
        std::string dir = directionToString(pair.first);
        bool locked = pair.second->getIsLocked();
        result += MessageFormatter::exitEntry(dir, locked);
    }

    return result;
}

std::string RoomFormatter::directionToString(Direction dir) {
    switch (dir) {
        case Direction::NORTH: return "North";
        case Direction::SOUTH: return "South";
        case Direction::EAST: return "East";
        case Direction::WEST: return "West";
        default: return "Unknown";
    }
}
