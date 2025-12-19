#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <string>
#include "NPC.hpp"

class Knight : public NPC {
 private:
    bool riddleSolved;
    bool swordGiven;

 public:
    Knight() : NPC("Knight",
                   "A noble knight guarding the armory's weapons."),
               riddleSolved(false),
               swordGiven(false) {}

    std::string interact(const Player& player) override;
    bool solveRiddle(const std::string& answer);
    bool hasGivenSword() const { return swordGiven; }
};

#endif  // KNIGHT_HPP
