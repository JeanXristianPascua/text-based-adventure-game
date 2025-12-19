#ifndef GUARD_HPP
#define GUARD_HPP

#include <string>
#include "NPC.hpp"

class Guard : public NPC {
 public:
    Guard() : NPC("Guard",
                  "A castle guard in worn armor, looking distressed.") {}

    std::string interact(const Player& player) override;
};

#endif  // GUARD_HPP
