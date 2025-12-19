#ifndef RIDDLE_PUZZLE_HPP
#define RIDDLE_PUZZLE_HPP

#include <string>

#include "Puzzle.hpp"

class RiddlePuzzle : public Puzzle {
 public:
    RiddlePuzzle()
        : Puzzle("Riddle Puzzle", "Solve the riddle to receive your prize.") {}
    std::string interact(const Player& player) override;
    //  bool solveRiddle(const std::string& answer, const Player& player);
};

#endif  // RIDDLE_PUZZLE_HPP
