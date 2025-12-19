#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "Direction.hpp"

class Room;
class Inventory;
class Item;
class WorldObject;

class Player {
 private:
    Room* currentRoom;
    Inventory* inventory;

 public:
    Player();
    ~Player();

    void look();
    void moveTo(Direction direction);
    void pickUpItem(const std::string& itemName);
    void useItem(const std::string& itemName, const std::string& targetName);
    Room* getCurrentRoom() const;
    void setCurrentRoom(Room* room);
    Inventory* getInventory() const;
    void dropItem(const std::string& itemName);
    //  void interactWithObject(const std::string& objectName);
};

#endif  // PLAYER_HPP
