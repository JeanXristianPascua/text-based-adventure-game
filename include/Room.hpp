#ifndef ROOM_HPP
#define ROOM_HPP

#include <map>
#include <string>
#include <vector>

#include "Direction.hpp"

class Player;
class Exit;
class Item;
class WorldObject;

class Room {
 private:
    std::string name;
    std::string description;
    std::vector<Item*> items;
    std::map<Direction, Exit*> exits;
    std::vector<WorldObject*> worldObjects;

 public:
    Room(const std::string& name, const std::string& description);
    virtual ~Room();

    // Entry notification (minimal display)
    void enter(const Player& player);

    // Exit management
    void addExit(Direction direction, Room* destination, Exit* exit = nullptr);
    Exit* getExit(Direction direction);

    // Item management
    void addItem(Item* item);
    Item* removeItem(const std::string& itemName);

    // WorldObject management
    void addWorldObject(WorldObject* object);
    WorldObject* getWorldObjectByName(const std::string& objectName);

    // Getters (for presentation layer)
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    std::vector<Item*> getItems() const { return items; }
    std::vector<WorldObject*> getWorldObjects() const { return worldObjects; }
    std::map<Direction, Exit*> getExits() const { return exits; }
};

#endif  // ROOM_HPP
