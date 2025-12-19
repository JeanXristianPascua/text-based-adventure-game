#include <string>
#include "Knight.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "StringUtils.hpp"

std::string Knight::interact(const Player& player) {
    if (swordGiven) {
        return "The knight nods at you respectfully.\n\n"
               "\"You have proven yourself worthy.\n"
               "Use that blade well, brave warrior.\"";
    }

    if (riddleSolved) {
        // Give the sword
        Room* currentRoom = player.getCurrentRoom();
        if (currentRoom) {
            // Check if sword already in room
            Item* existingSword = currentRoom->removeItem("sword");
            if (existingSword) {
                // Put it back
                currentRoom->addItem(existingSword);
                return "The knight gestures to the sword:\n\n"
                       "\"Take it, you've earned it!\"";
            } else {
                // Add sword to room
                Item* sword = new Item("sword",
                                      "Sword",
                                      "A sharp steel blade, "
                                      "perfectly balanced for combat. "
                                      "It gleams in the light.");
                currentRoom->addItem(sword);
                swordGiven = true;

                return "The knight bows and "
                       "presents you with a magnificent sword!\n\n"
                       "\"You have proven your wit and wisdom.\n"
                       "This blade has served me well. "
                       "May it serve you better.\"\n\n"
                       "The sword now lies before you. You should take it.";
            }
        }

        return "The knight nods approvingly.";
    }

    return "The knight blocks your path to the weapons.\n\n"
           "\"Hold, traveler! These weapons are not for the taking.\n"
           "Only those who prove their wisdom may claim a blade.\n\n"
           "Answer my riddle correctly, and I shall grant you\n"
           "the finest sword in this armory:\n\n"
           "    I am taken from a mine, and shut up in a wooden case,\n"
           "    from which I am never released, and yet I am used\n"
           "    by almost every person. What am I?\"\n\n"
           "Type 'answer <your answer>' to respond.";
}

bool Knight::solveRiddle(const std::string& answer) {
    // Accept various forms of the correct answer (case-insensitive)
    if (StringUtils::equalsIgnoreCase(answer, "pencil") ||
        StringUtils::equalsIgnoreCase(answer, "a pencil") ||
        StringUtils::equalsIgnoreCase(answer, "pencil lead") ||
        StringUtils::equalsIgnoreCase(answer, "lead")) {
        riddleSolved = true;
        return true;
    }

    return false;
}
