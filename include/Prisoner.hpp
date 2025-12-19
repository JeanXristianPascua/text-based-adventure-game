#ifndef PRISONER_HPP
#define PRISONER_HPP

#include <string>
#include "NPC.hpp"

class Prisoner : public NPC {
 public:
    Prisoner() : NPC("Prisoner",
                     "A weary prisoner with knowing eyes.") {}

    std::string interact(const Player& player) override;
};

#endif  // PRISONER_HPP
