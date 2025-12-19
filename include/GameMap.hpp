#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include <string>
#include <vector>

#include "Environment.hpp"
#include "Room.hpp"

class GameMap {
 private:
    std::vector<Environment*> environments;
    CastleMain* mainCastle;
    CastleDungeon* dungeon;
    CastleCourtyard* courtyard;
    void connectEnvironments();

 public:
    GameMap();
    ~GameMap();
    void generateWorld();
    Room* getStartingRoom() const;
    Room* getRoomByName(const std::string& name) const;
    const std::vector<Environment*>& getEnvironments() const {
        return environments;
    }
};

#endif  // GAMEMAP_HPP
