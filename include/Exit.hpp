#ifndef EXIT_HPP
#define EXIT_HPP

#include <string>
#include "Direction.hpp"

class Player;
class Item;
class Room;

class Exit {
 private:
    Room* destination;           // destination room
    Direction direction;         // exit direction
    std::string requiredKeyId;   // key required to unlock
    std::string description;     // exit description
    bool isLocked;               // lock status

 public:
    Exit(Room* dest,
         Direction dir,
         bool locked = false,
         const std::string& keyId = "",
         const std::string& desc = "");

    bool canPass(const Player& player);
    bool unlock(const Item& item);

    Room* getDestination() const { return destination; }
    bool getIsLocked() const { return isLocked; }
};

#endif  // EXIT_HPP
