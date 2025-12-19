#include <string>
#include "BookPile.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "Item.hpp"

std::string BookPile::interact(const Player& player) {
    // Add Prison Key to the current room
    Room* currentRoom = player.getCurrentRoom();
    if (currentRoom) {
        // Check if key already added
        if (currentRoom->removeItem("prison key")) {
            // Put it back, already there
            Item* key = new Item("prison_key",
                                "Prison Key",
                                "An old iron key with rust spots. "
                                "It looks like it unlocks a cell door.");
            currentRoom->addItem(key);
            return "You've already searched through these books.";
        } else {
            // Add the key
            Item* prisonKey = new Item("prison_key",
                                      "Prison Key",
                                      "An old iron key with rust spots. "
                                      "It looks like it unlocks a cell door.");
            currentRoom->addItem(prisonKey);
            return "You search through the pile of dusty books...\n"
                   "Hidden among the pages, you find a Prison Key!\n"
                   "You should take it.";
        }
    }
    return "You search the books but find nothing.";
}
