#include <string>
#include "MysteriousBook.hpp"
#include "Player.hpp"

std::string MysteriousBook::interact(const Player& player) {
    // This should trigger death - return special death message
    return "DEATH:You reach out to touch the mysterious book...\n"
           "Dark energy surges through your body!\n"
           "The ancient curse consumes you.\n"
           "YOU DIED.";
}
