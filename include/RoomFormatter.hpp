#ifndef ROOM_FORMATTER_HPP
#define ROOM_FORMATTER_HPP

#include <string>
#include <vector>
#include <numeric>
#include <map>
#include "MessageFormatter.hpp"
#include "Direction.hpp"

class Room;
class Item;
class WorldObject;
class Exit;

class RoomFormatter {
 public:
    // Format a full room description
    static std::string formatRoom(const Room* room);

    // Format just the entry message
    static std::string formatEntry(const Room* room);

 private:
    static std::string formatItemsList(const std::vector<Item*>& items);
    static std::string formatWorldObjectsList(
        const std::vector<WorldObject*>& objects);
    static std::string formatExitsList(
        const std::map<Direction, Exit*>& exits);
    static std::string directionToString(Direction dir);

    RoomFormatter() = delete;  // Utility class
};

#endif  // ROOM_FORMATTER_HPP
