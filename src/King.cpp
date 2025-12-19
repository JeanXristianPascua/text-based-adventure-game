#include <string>
#include "King.hpp"
#include "Player.hpp"
#include "Inventory.hpp"

std::string King::interact(const Player& player) {
    Inventory* inv = player.getInventory();

    // Check what items the player has
    bool hasPoisonSword = inv->hasItem("poison_sword");
    bool hasSword = inv->hasItem("sword");

    if (hasPoisonSword) {
        // WINNING SCENARIO - Player has poison sword
        return "VICTORY:You step forward, brandishing the Poison Sword.\n\n"
               "The King's eyes widen in fear "
               "as he recognizes the deadly weapon.\n\n"
               "\"No! That blade... it cannot be!\"\n\n"
               "You strike swiftly. The poisoned blade finds its mark.\n"
               "The tyrant falls from his throne, defeated at last.\n\n"
               "The path to the Secret Chamber opens before you...\n"
               "The throne room door to the "
               " east unlocks with a resounding click.";
    } else if (hasSword) {
        // DEATH SCENARIO - Player only has regular sword
        return "DEATH:You raise your sword and challenge the King!\n\n"
               "\"Foolish mortal! A simple blade cannot harm me!\"\n\n"
               "The King rises from his throne, "
               "drawing his own enchanted weapon.\n"
               "He moves with supernatural speed.\n\n"
               "Your sword shatters against his magical defenses.\n"
               "The King's blade pierces your heart.\n\n"
               "YOU DIED.\n\n"
               "Perhaps a more... toxic approach would have worked better.";
    } else {
        // TAUNT SCENARIO - Player has nothing useful
        return "The King looks at you and laughs mockingly.\n\n"
               "\"BWAHAHAHAHA! You dare approach me with nothing?\n"
               "You have no weapon that can challenge my power!\n\n"
               "Begone from my sight, or my guards will remove you!\"\n\n"
               "The King waves his hand dismissively.\n"
               "You are not ready to face him yet.";
    }

    // Default fallback
    return "The King watches you with cruel amusement from his throne.";
}
