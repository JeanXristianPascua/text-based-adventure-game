#ifndef HORSE_HPP
#define HORSE_HPP

#include <string>

#include "WorldObject.hpp"

class Horse : public WorldObject {
 public:
    Horse() : WorldObject("Horse", "A powerful and dangerous war horse.") {}
    std::string interact(const Player& player) override;
};

#endif  // HORSE_HPP
