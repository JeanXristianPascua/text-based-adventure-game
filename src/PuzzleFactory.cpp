#include <string>
#include "PuzzleFactory.hpp"

Puzzle* PuzzleFactory::createPuzzle(const std::string& type) {
    if (type == "RiddlePuzzle") {
        return new RiddlePuzzle();
    } else {
        return nullptr;
    }
}
