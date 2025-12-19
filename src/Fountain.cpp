#include <string>
#include "Fountain.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "Item.hpp"

std::string Fountain::interact(const Player& player) {
    // Add Poison Flower to the current room
    Room* currentRoom = player.getCurrentRoom();
    if (currentRoom) {
        // Check if flower already added
        if (currentRoom->removeItem("poison flower")) {
            // Put it back, already there
            Item* flower = new Item("poison_flower",
                                   "Poison Flower",
                                   "A beautiful but deadly "
                                   "flower with deep purple petals. "
                                   "Its toxic properties could be useful...");
            currentRoom->addItem(flower);
            return "You've already searched the fountain.";
        } else {
            // Add the flower
            Item* poisonFlower = new Item("poison_flower",
                                         "Poison Flower",
                                         "A beautiful but deadly "
                                         "flower with deep purple petals. "
                                         "Its toxic properties "
                                         "could be useful...");
            currentRoom->addItem(poisonFlower);
            return "You search around the fountain and find a Poison Flower!\n"
                   "Beautiful but deadly. You should take it.";
        }
    }
    return "You search the fountain but find nothing.";
}
