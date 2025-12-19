#include <string>
#include "Horse.hpp"
#include "Player.hpp"

std::string Horse::interact(const Player& player) {
    // This should trigger death - return special death message
    return "DEATH:You approach the war horse...\n"
           "It rears up and kicks you with tremendous force!\n"
           "You feel your bones shatter.\n"
           "YOU DIED.";
}
