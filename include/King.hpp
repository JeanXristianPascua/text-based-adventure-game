#ifndef KING_HPP
#define KING_HPP

#include <string>
#include "NPC.hpp"

class King : public NPC {
 public:
    King() : NPC("King",
                 "The tyrannical King sits upon his throne, "
                 "watching you with cruel eyes.") {}

    std::string interact(const Player& player) override;
};

#endif  // KING_HPP
