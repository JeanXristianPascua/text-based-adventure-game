#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>

class GameState {
 private:
    bool running;
    bool playerDied;
    bool playerWon;
    int puzzlesSolved;
    std::string deathReason;

 public:
    GameState();

    // Running state
    bool isRunning() const { return running; }
    void setRunning(bool value) { running = value; }
    void stop() { running = false; }

    // Death state
    bool hasPlayerDied() const { return playerDied; }
    void setPlayerDeath(const std::string& reason);
    std::string getDeathReason() const { return deathReason; }

    // Victory state
    bool hasPlayerWon() const { return playerWon; }
    void setPlayerVictory() { playerWon = true; }

    // Puzzle tracking
    void incrementPuzzlesSolved() { puzzlesSolved++; }
    void setPuzzlesSolved(int count) { puzzlesSolved = count; }
    int getPuzzlesSolved() const { return puzzlesSolved; }

    // Game over checks
    bool isGameOver() const { return playerDied || playerWon; }
};

#endif  // GAMESTATE_HPP
