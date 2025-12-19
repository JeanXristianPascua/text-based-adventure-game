#include <string>
#include "NPCFactory.hpp"

NPC* NPCFactory::createNPC(const std::string& type) {
    if (type == "Guard") {
        return new Guard();
    } else if (type == "Prisoner") {
        return new Prisoner();
    } else if (type == "Knight") {
        return new Knight();
    } else if (type == "King") {
        return new King();
    } else {
        return nullptr;
    }
}
