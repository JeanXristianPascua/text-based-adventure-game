#ifndef NPC_FACTORY_HPP
#define NPC_FACTORY_HPP

#include <string>
#include "NPC.hpp"
#include "Guard.hpp"
#include "Prisoner.hpp"
#include "Knight.hpp"
#include "King.hpp"

class NPCFactory {
 public:
    static NPC* createNPC(const std::string& type);
};

#endif  // NPC_FACTORY_HPP
