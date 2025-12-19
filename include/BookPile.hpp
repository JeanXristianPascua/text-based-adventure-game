#ifndef BOOKPILE_HPP
#define BOOKPILE_HPP

#include <string>
#include "WorldObject.hpp"

class BookPile : public WorldObject {
 public:
    BookPile() : WorldObject("Book Pile", "A large pile of dusty old books.") {}
    std::string interact(const Player& player) override;
};

#endif  // BOOKPILE_HPP
