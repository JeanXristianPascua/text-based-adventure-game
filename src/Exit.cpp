#include "Exit.hpp"

#include <iostream>
#include <string>

#include "Item.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "MessageFormatter.hpp"

// Constructor
Exit::Exit(Room* dest,
           Direction dir,
           bool locked,
           const std::string& keyId,
           const std::string& desc)
    : destination(dest),
      direction(dir),
      isLocked(locked),
      requiredKeyId(keyId),
      description(desc) {}

// Checks if the player can pass through the exit
bool Exit::canPass(const Player& player) {
    if (isLocked) {
        std::cout << MessageFormatter::exitLocked();
        if (!requiredKeyId.empty()) {
            std::cout << MessageFormatter::needKeyToUnlock() << std::endl;
        } else {
            std::cout <<
                "You need to find another way to unlock it." << std::endl;
        }
        return false;
    }
    return true;
}

// Checks if player can unlock the exit with a given item
bool Exit::unlock(const Item& item) {
    if (!isLocked) {
        std::cout <<
            MessageFormatter::unlockAlreadyUnlocked() << std::endl;
        return false;
    }

    if (item.getId() == requiredKeyId) {
        isLocked = false;
        std::cout <<
            MessageFormatter::unlockSuccess(item.getName()) << std::endl;
        return true;
    }

    std::cout << MessageFormatter::unlockWrongItem() << std::endl;
    return false;
}
