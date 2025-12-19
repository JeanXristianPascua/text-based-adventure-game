#ifndef FOUNTAIN_HPP
#define FOUNTAIN_HPP

#include <string>

#include "WorldObject.hpp"

class Fountain : public WorldObject {
 public:
    Fountain()
        : WorldObject(
              "Fountain",
              "A beautiful stone fountain surrounded by lush greenery.") {}
    std::string interact(const Player& player) override;
};

#endif  // FOUNTAIN_HPP
