#include <string>

#include "Guard.hpp"
#include "Player.hpp"

std::string Guard::interact(const Player& player) {
    return "The guard fidgets nervously, eyes darting around the room.\n\n"
           "\"I seem to have misplaced something… "
           "something I can't afford to lose.\n"
           "I remember handling it near the place "
           "where knowledge sleeps...\n"
           "Maybe those silent, dusty companions have seen it?\n\n"
           "If the Captain finds out, I’m in serious trouble!\"";
}
