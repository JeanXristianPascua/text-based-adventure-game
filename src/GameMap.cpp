#include <string>
#include <iostream>
#include "GameMap.hpp"
#include "Exit.hpp"

GameMap::GameMap()
    : mainCastle(nullptr), dungeon(nullptr), courtyard(nullptr) {}

GameMap::~GameMap() {
    for (Environment* env : environments) {
        delete env;
    }
    environments.clear();
}

void GameMap::generateWorld() {
    // Create all environments
    courtyard = new CastleCourtyard();
    courtyard->generateRooms();
    environments.push_back(courtyard);

    mainCastle = new CastleMain();
    mainCastle->generateRooms();
    environments.push_back(mainCastle);

    dungeon = new CastleDungeon();
    dungeon->generateRooms();
    environments.push_back(dungeon);

    // Connect all environments together
    connectEnvironments();
}

void GameMap::connectEnvironments() {
    // Get key rooms from each environment

    // Bottom row (outer courtyard)
    Room* mainGate
        = courtyard->getRoomByName("Main Gate");      // Room #2 (START)

    // Middle row (main castle)
    Room* courtyardRoom = mainCastle->getRoomByName("Courtyard"); // Room #5

    // Right side (dungeon)
    Room* prison = dungeon->getRoomByName("Prison");             // Room #6

    // Main Gate (#2) to Courtyard (#5)
    if (mainGate && courtyardRoom) {
        mainGate->addExit(Direction::NORTH, courtyardRoom,
                         new Exit(courtyardRoom, Direction::NORTH));
        courtyardRoom->addExit(Direction::SOUTH, mainGate,
                              new Exit(mainGate, Direction::SOUTH));
    } else {
        std::cerr <<
            "Error: Could not connect Main Gate to Courtyard"
            << std::endl;
    }

    // Connect Courtyard (#5) to Prison (#6) - LOCKED
    if (courtyardRoom && prison) {
        courtyardRoom->addExit(Direction::EAST, prison,
            new Exit(prison, Direction::EAST, true, "prison_key",
                "A heavy iron door leads to the prison. It's locked."));
        prison->addExit(Direction::WEST, courtyardRoom,
            new Exit(courtyardRoom, Direction::WEST));
    } else {
        std::cerr <<
            "Error: Could not connect Courtyard to Prison" << std::endl;
    }
}

Room* GameMap::getStartingRoom() const {
    if (courtyard) {
        Room* startRoom = courtyard->getRoomByName("Main Gate");
        if (!startRoom) {
            std::cerr <<
                "Warning: Starting room 'Main Gate' not found!" << std::endl;
        }
        return startRoom;
    }
    std::cerr << "Error: Courtyard environment not initialized!" << std::endl;
    return nullptr;
}

Room* GameMap::getRoomByName(const std::string& name) const {
    for (Environment* env : environments) {
        Room* room = env->getRoomByName(name);
        if (room) {
            return room;
        }
    }
    return nullptr;
}
