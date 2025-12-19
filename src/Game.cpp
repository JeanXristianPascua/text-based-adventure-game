#include "Game.hpp"

#include <iostream>
#include <string>

#include "Player.hpp"
#include "GameMap.hpp"
#include "GameState.hpp"
#include "InputParser.hpp"
#include "CommandExecutor.hpp"
#include "Room.hpp"
#include "MessageFormatter.hpp"

Game::Game() {
    player = new Player();
    gameState = new GameState();
    inputParser = new InputParser();
    gameMap = nullptr;
    commandExecutor = new CommandExecutor(player, gameState, inputParser);
}

Game::~Game() {
    delete player;
    delete gameState;
    delete inputParser;
    delete gameMap;
    delete commandExecutor;
}

void Game::initializeWorld() {
    // Create the game map
    gameMap = new GameMap();
    gameMap->generateWorld();

    // Set the starting room (Main Gate)
    Room* startingRoom = gameMap->getStartingRoom();
    if (startingRoom) {
        player->setCurrentRoom(startingRoom);
        startingRoom->enter(*player);
    } else {
        std::cerr << "Error: Could not find starting room!" << std::endl;
        gameState->stop();
    }
}

void Game::start() {
    std::cout << MessageFormatter::welcomeMessage() << std::endl;

    initializeWorld();

    if (gameState->isRunning()) {
        gameLoop();
    }
}

void Game::gameLoop() {
    std::string input;

    while (gameState->isRunning()) {
        std::cout << "\n> ";
        std::getline(std::cin, input);

        if (!input.empty()) {
            InputParser::Command cmd = inputParser->parseCommand(input);
            commandExecutor->executeCommand(cmd);
        }

        checkEndConditions();
    }
}

void Game::checkEndConditions() {
    // Check for victory (player entered Secret Chamber)
    Room* currentRoom = player->getCurrentRoom();
    if (currentRoom && currentRoom->getName() == "Secret Chamber") {
        if (!gameState->hasPlayerWon()) {
            gameState->setPlayerVictory();
        }
    }

    // Display end game messages
    if (gameState->hasPlayerWon()) {
        std::cout << MessageFormatter::victoryBanner() << std::endl;
        gameState->stop();
    } else if (gameState->hasPlayerDied()) {
        std::cout << MessageFormatter::gameOverBanner() << std::endl;
        gameState->stop();
    }
}
