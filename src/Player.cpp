#include "Player.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Direction.hpp"
#include "Exit.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Room.hpp"
#include "StringUtils.hpp"
#include "MessageFormatter.hpp"
#include "RoomFormatter.hpp"

Player::Player() : currentRoom(nullptr) { inventory = new Inventory(); }

Player::~Player() { delete inventory; }

void Player::look() {
    if (currentRoom) {
        // Use RoomFormatter instead of Room::examine()
        std::cout << RoomFormatter::formatRoom(currentRoom) << std::endl;
    } else {
        std::cout << MessageFormatter::youAreNowhere() << std::endl;
    }
}

void Player::moveTo(Direction direction) {
    if (!currentRoom) {
        std::cout << MessageFormatter::youAreNowhere() << std::endl;
        return;
    }

    Exit* exit = currentRoom->getExit(direction);

    if (!exit) {
        std::cout << MessageFormatter::cannotGoThatWay() << std::endl;
        return;
    }

    if (!exit->canPass(*this)) {
        return;  // canPass already prints the reason
    }

    Room* destination = exit->getDestination();
    if (destination) {
        currentRoom = destination;
        currentRoom->enter(*this);
    }
}

void Player::pickUpItem(const std::string& itemName) {
    if (!currentRoom) {
        std::cout << MessageFormatter::youAreNowhere() << std::endl;
        return;
    }

    Item* item = currentRoom->removeItem(itemName);
    if (item) {
        if (inventory->addItem(*item)) {
            std::cout << MessageFormatter::pickupSuccess(item->getName())
                      << std::endl;

            // Check for item combinations after picking up
            std::string combinationMessage = inventory->processCombinations();
            if (!combinationMessage.empty()) {
                std::cout << combinationMessage << std::endl;
            }

            delete item;
        } else {
            std::cout << MessageFormatter::pickupAlreadyHave() << std::endl;
            currentRoom->addItem(item);  // Put it back
        }
    } else {
        std::cout << MessageFormatter::pickupNotFound(itemName) << std::endl;
    }
}

void Player::useItem(const std::string& itemName,
                     const std::string& targetName) {
    // Search for item using case-insensitive comparison
    std::vector<Item*> allItems = inventory->getAllItems();
    auto it = std::find_if(allItems.begin(), allItems.end(),
        [&itemName](Item* invItem) {
        return StringUtils::equalsIgnoreCase(invItem->getName(), itemName);
    });

    Item* item = (it != allItems.end()) ? *it : nullptr;

    if (!item) {
        std::cout << MessageFormatter::dropNotFound(itemName) << std::endl;
        return;
    }

    // Check if target is a direction (for doors/exits)
    Direction dir;
    bool isDirection = false;

    std::string targetLower = StringUtils::toLower(targetName);
    if (targetLower == "north" || targetLower == "n") {
        dir = NORTH;
        isDirection = true;
    } else if (targetLower == "south" || targetLower == "s") {
        dir = SOUTH;
        isDirection = true;
    } else if (targetLower == "east" || targetLower == "e") {
        dir = EAST;
        isDirection = true;
    } else if (targetLower == "west" || targetLower == "w") {
        dir = WEST;
        isDirection = true;
    }

    if (isDirection) {
        Exit* exit = currentRoom->getExit(dir);
        if (exit) {
            exit->unlock(*item);
        } else {
            std::cout << MessageFormatter::noExitInDirection() << std::endl;
        }
    } else {
        std::cout << MessageFormatter::notSureHowToUse() << std::endl;
    }
}

Room* Player::getCurrentRoom() const { return currentRoom; }

void Player::setCurrentRoom(Room* room) { currentRoom = room; }

Inventory* Player::getInventory() const { return inventory; }

void Player::dropItem(const std::string& itemName) {
    Item* item = inventory->getItemByName(itemName);
    if (!item) {
        std::cout << MessageFormatter::dropNotFound(itemName) << std::endl;
        return;
    }

    // Create a copy of the item to add to the room
    Item* droppedItem =
        new Item(item->getId(), item->getName(), item->examine());
    currentRoom->addItem(droppedItem);

    // Remove from inventory
    std::string itemId = item->getId();
    inventory->removeItem(itemId);

    std::cout << MessageFormatter::dropSuccess(itemName) << std::endl;
}
