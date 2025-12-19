#ifndef PUZZLE_FACTORY_HPP
#define PUZZLE_FACTORY_HPP

#include <string>

#include "Puzzle.hpp"
#include "RiddlePuzzle.hpp"

class PuzzleFactory {
 public:
    static Puzzle* createPuzzle(const std::string& type);
};

#endif  // PUZZLE_FACTORY_HPP
