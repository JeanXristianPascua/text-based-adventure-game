#include <string>
#include "RiddlePuzzle.hpp"

#include "Item.hpp"
#include "Player.hpp"

std::string RiddlePuzzle::interact(const Player& player) {
    return "I am sharp and made of steel. What am I?\n";
}

// bool RiddlePuzzle::solveRiddle(const std::string& answer, const Player&
// player) {
//     if (answer == "sword") {
//         Item* sword = new Item("sword001", "Sword", "A sharp blade made of
//         steel, "
//             "perfect for combat.");
//         player.addItem(prize);
//         return true;
//     }
//     return false;
// }
