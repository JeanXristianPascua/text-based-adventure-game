#include <string>

#include "Prisoner.hpp"
#include "Player.hpp"

std::string Prisoner::interact(const Player& player) {
    return "The prisoner grips the bars and whispers urgently:\n\n"
           "\"You seek to defeat the King? Listen well...\n\n"
           "A simple blade will not pierce his defenses.\n"
           "But I've heard tales of a deadly poison on these grounds.\n\n"
           "Coat your sword with the toxin, and you may stand a chance.\n"
           "The combination of steel and poison... that is the key!\"\n\n"
           "He retreats back into the shadows.";
}
