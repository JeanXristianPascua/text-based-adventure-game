#ifndef MYSTERIOUS_BOOK_HPP
#define MYSTERIOUS_BOOK_HPP

#include <iostream>
#include <string>

#include "WorldObject.hpp"

class MysteriousBook : public WorldObject {
 public:
    MysteriousBook()
        : WorldObject("Mysterious Book",
                      "A strange, glowing book with ancient symbols.") {}
    std::string interact(const Player& player) override;
};

#endif  // MYSTERIOUS_BOOK_HPP
