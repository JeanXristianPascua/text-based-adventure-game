#include <string>
#include "GameState.hpp"

GameState::GameState()
    : running(true),
      playerDied(false),
      playerWon(false),
      puzzlesSolved(0),
      deathReason("") {}

void GameState::setPlayerDeath(const std::string& reason) {
    playerDied = true;
    deathReason = reason;
    running = false;
}
