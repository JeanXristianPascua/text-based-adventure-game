#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <iostream>
#include <string>

#include "Player.hpp"

class Puzzle {
 private:
    std::string name;
    std::string description;

 public:
    Puzzle(const std::string& name, const std::string& description)
        : name(name), description(description) {}
    virtual ~Puzzle() = default;
    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }
    virtual std::string interact(const Player& player) = 0;
};

#endif  // PUZZLE_HPP
